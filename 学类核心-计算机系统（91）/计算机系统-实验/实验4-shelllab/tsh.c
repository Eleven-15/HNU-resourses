/*
 * tsh - A tiny shell program with job control
 * 202108010206 ArcticWolf
 */
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Misc manifest constants */
#define MAXLINE 1024   /* max line size */
#define MAXARGS 128    /* max args on a command line */
#define MAXJOBS 16     /* max jobs at any point in time */
#define MAXJID 1 << 16 /* max job ID */

/* Job states */
#define UNDEF 0 /* undefined */
#define FG 1    /* running in foreground */
#define BG 2    /* running in background */
#define ST 3    /* stopped */

/*
 * Jobs states: FG (foreground), BG (background), ST (stopped)
 * Job state transitions and enabling actions:
 *     FG -> ST  : ctrl-z
 *     ST -> FG  : fg command
 *     ST -> BG  : bg command
 *     BG -> FG  : fg command
 * At most 1 job can be in the FG state.
 */

/* Global variables */
extern char **environ;   /* defined in libc */
char prompt[] = "tsh> "; /*命令行提示符(DO NOT CHANGE) */
int verbose = 0;         /*是否输出额外信息*/
int nextjid = 1;         /*要分配的下一个作业ID*/
char sbuf[MAXLINE];      /* for composing sprintf messages */

struct job_t
{                          /* The job struct */
    pid_t pid;             /* job PID */
    int jid;               /* job ID [1, 2, ...] */
    int state;             /* UNDEF, BG, FG, or ST */
    char cmdline[MAXLINE]; /* command line */
};
struct job_t jobs[MAXJOBS]; /* The job list */
/* End global variables */

/* Function prototypes */

/* Here are the functions that you will implement */
void eval(char *cmdline);
int builtin_cmd(char **argv);
void do_bgfg(char **argv);
void waitfg(pid_t pid);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);

/* Here are helper routines that we've provided for you */
int parseline(const char *cmdline, char **argv);
void sigquit_handler(int sig);

void clearjob(struct job_t *job);
void initjobs(struct job_t *jobs);
int maxjid(struct job_t *jobs);
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline);
int deletejob(struct job_t *jobs, pid_t pid);
pid_t fgpid(struct job_t *jobs);
struct job_t *getjobpid(struct job_t *jobs, pid_t pid);
struct job_t *getjobjid(struct job_t *jobs, int jid);
int pid2jid(pid_t pid);
void listjobs(struct job_t *jobs);

void usage(void);
void unix_error(char *msg);
void app_error(char *msg);
typedef void handler_t(int);
handler_t *Signal(int signum, handler_t *handler);

/*
 * main - shell的主函数
 */
int main(int argc, char **argv)
{
    char c;
    char cmdline[MAXLINE];
    int emit_prompt = 1; /* emit prompt (default) */

    /* 将stderr重定向到stdout（这样驱动程序将获得连接到stdout的管道上的所有输出） */
    dup2(1, 2);

    /* 解析命令行 */
    while ((c = getopt(argc, argv, "hvp")) != EOF)
    {
        switch (c)
        {
        case 'h': /* 打印提示信息 */
            usage();
            break;
        case 'v': /* 发出附加诊断信息 */
            verbose = 1;
            break;
        case 'p':            /* 不打印提示 */
            emit_prompt = 0; /* 便于自动测试 */
            break;
        default:
            usage();
        }
    }

    /* Install the signal handlers */

    /* These are the ones you will need to implement */
    Signal(SIGINT, sigint_handler);   /* ctrl-c */
    Signal(SIGTSTP, sigtstp_handler); /* ctrl-z */
    Signal(SIGCHLD, sigchld_handler); /* Terminated or stopped child */

    /* This one provides a clean way to kill the shell */
    Signal(SIGQUIT, sigquit_handler);

    /* 初始化 job list */
    initjobs(jobs);

    /* Execute the shell's read/eval loop */
    while (1)
    {

        /* Read command line */
        if (emit_prompt)
        {
            printf("%s", prompt);
            fflush(stdout); // 清空缓存区
        }
        if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
            app_error("fgets error");
        if (feof(stdin))
        { /* End of file (ctrl-d) */
            fflush(stdout);
            exit(0);
        }

        /* Evaluate the command line */
        eval(cmdline);
        fflush(stdout);
        fflush(stdout);
    }

    exit(0); /* control never reaches here */
}

/*
* eval - 分析命令，并派生子进程执行 主要功能是解析cmdline并运行
如果用户请求了一个内置命令（quit、jobs、bg或fg），则立即执行。否则，派生一个子进程并在该子进程的上下文中运行作业。如果作业正在前台运行，请等待它终止，然后返回。注意：每个子进程都必须有一个唯一的进程组ID，这样当我们在键盘上键入ctrl-c（ctrl-z）时，我们的后台子进程就不会从内核接收SIGINT（SIGTSTP）。
*/
void eval(char *cmdline)
{
    char *argv[MAXARGS]; // execve()函数的参数
    int state = UNDEF;   // 工作状态，FG或BG
    sigset_t set;
    pid_t pid; // 进程id

    // 处理输入的数据
    if (parseline(cmdline, argv) == 1) // 解析命令行，返回给argv数组
        state = BG;
    else
        state = FG;
    if (argv[0] == NULL) // 若命令行为空，parseline也会返回1，但对argv[0]判定后，eval在这里直接返回
        return;

    // 如果不是内置命令
    if (!builtin_cmd(argv)) // 若是内置命令，builtin_cmd(argv)会执行，若该函数返回0，则表示非内置命令
    {
        // 初始化信号集set并把SIGINT SIGTSTP SIGCHLD三个信号放入信号集中，方便管理
        if (sigemptyset(&set) < 0)
            unix_error("sigemptyset error");
        if (sigaddset(&set, SIGINT) < 0 || sigaddset(&set, SIGTSTP) < 0 || sigaddset(&set, SIGCHLD) < 0)
            unix_error("sigaddset error");

        // 阻塞SIGCHLD信号，具体原因在书P541有解释
        // 主要是防止fork之后调度执行子进程并在addjob之前结束子进程，
        // 此时SIGCHLD信号使父进程将子进程回收，这会导致 addjob 和 deletejob 函数执行错位
        // 结果是删除一个不存在的进程号，添加一个不存在且永不会被删除的进程号
        if (sigprocmask(SIG_BLOCK, &set, NULL) < 0)
            unix_error("sigprocmask error");

        if ((pid = fork()) < 0) // fork创建子进程失败
            unix_error("fork error");
        else if (pid == 0) // fork创建子进程
        {
            // 子进程控制流从这里开始

            if (sigprocmask(SIG_UNBLOCK, &set, NULL) < 0) // 解除阻塞
                unix_error("sigprocmask error");

            // 函数原型 int setpgid(pid_t pid,pid_t pgid);
            // 将pid进程的进程组ID设置成pgid
            // 如果参数pid为0，则会用来设置该进程的组识别码，
            // 如果参数pgid为0，则由pid指定的进程ID将用作进程组ID
            // 一个进程只能为它自己或它的子进程设置进程组ID,不能为其父进程设置ID。
            if (setpgid(0, 0) < 0) // 设置子进程id（实际上并没有分进程组，因为一人一组）
                unix_error("setpgid error");

            if (execve(argv[0], argv, environ) < 0)
            {
                printf("%s: Command not found\n", argv[0]);
                exit(0);
            }
        }

        // 父进程控制流从这里开始
        addjob(jobs, pid, state, cmdline); // 将当前进程添加进jobs中，参数为当前进程pid,state,cmdline

        // 恢复受阻塞的信号 SIGINT SIGTSTP SIGCHLD
        if (sigprocmask(SIG_UNBLOCK, &set, NULL) < 0)
            unix_error("sigprocmask error");

        // 判断子进程类型并做处理
        if (state == FG)
            waitfg(pid); // 等待子进程的前台作业完成
        else
            printf("[%d] (%d) %s", pid2jid(pid), pid, cmdline); // 将进程id映射到job id
    }
    return;
}

/*
 * parceline - 分析命令行并构建argv数组
单引号中的字符被视为一个参数。如果用户已请求BG作业，则返回true；如果用户已申请FG作业，则为false
 */
int parseline(const char *cmdline, char **argv)
{
    static char array[MAXLINE]; /* 创建cmd的备份 */
    char *buf = array;          /* 遍历命令行的ptr */
    char *delim;                /* 迭代指针（指向当前处理位置） */
    int argc;                   /* argv向量个数 */
    int bg;                     /* 是否后台运行标志 */

    strcpy(buf, cmdline);         // 在本地生成cmdline的副本buf
    buf[strlen(buf) - 1] = ' ';   /*将cmdline最后的'\n'替换为空格符*/
    while (*buf && (*buf == ' ')) /*忽略前导空格*/
        buf++;

    /*生成参数向量（agrv）列表*/
    argc = 0;
    if (*buf == '\'')
    {
        buf++;
        delim = strchr(buf, '\'');
    }
    else
    {
        delim = strchr(buf, ' ');
    }

    while (delim)
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /*忽略空格*/
            buf++;

        if (*buf == '\'')
        {
            buf++;
            delim = strchr(buf, '\'');
        }
        else
        {
            delim = strchr(buf, ' ');
        }
    }
    argv[argc] = NULL;

    if (argc == 0) /*若cmdline是空的，返回1*/
        return 1;

    /*是否后台运行*/
    if ((bg = (*argv[argc - 1] == '&')) != 0)
    {
        argv[--argc] = NULL; // 去掉&
    }
    return bg; // 若最后有&，则bg=1，parseline会返回1
}

/*
 * builtin_cmd：解析和执行bulidin命令，包括 quit, fg, bg, jobs
 */
int builtin_cmd(char **argv)
{
    if (!strcmp(argv[0], "quit")) // 如果命令是quit，退出
        exit(0);
    else if (!strcmp(argv[0], "bg") || !strcmp(argv[0], "fg")) // 如果是bg或者fg命令，执行do_fgbg函数
        do_bgfg(argv);
    else if (!strcmp(argv[0], "jobs")) // 如果命令是jobs，列出正在运行和停止的后台作业
        listjobs(jobs);
    else
        return 0; /* 不是内置命令，以0返回eval */
    return 1;
}

/*
 * do_bgfg - 执行bg和fg命令
 */
void do_bgfg(char **argv)
{
    int num;
    struct job_t *job;
    // 没有参数的fg/bg不符合规定
    if (!argv[1])
    { // 命令行为空
        printf("%s command requires PID or %%jobid argument\n", argv[0]);
        return;
    }

    // strtol函数原型：long int strtol(const char *nptr, char **endptr, int base);
    // strtol函数会将参数nptr字符串根据参数base来转换成长整型数，参数base范围从2至36。

    // 检测fg/bg参数，其中%开头的数字是JobID，纯数字的是PID
    // 找到jobID或PID后通过这个找出job
    if (argv[1][0] == '%')
    {                                                   // 解析jid
        if ((num = strtol(&argv[1][1], NULL, 10)) <= 0) // 获取jid
        {
            printf("%s: argument must be a PID or %%jobid\n", argv[0]); // 失败,打印错误消息
            return;
        }
        if ((job = getjobjid(jobs, num)) == NULL) // 根据jid获取job
        {
            printf("%%%d: No such job\n", num); // 没找到对应的job
            return;
        }
    }
    else
    {                                               // 解析PID
        if ((num = strtol(argv[1], NULL, 10)) <= 0) // 获取PID
        {
            printf("%s: argument must be a PID or %%jobid\n", argv[0]); // 失败,打印错误消息
            return;
        }
        if ((job = getjobpid(jobs, num)) == NULL) // 根据PID获取job
        {
            printf("(%d): No such process\n", num); // 没找到对应的进程
            return;
        }
    }

    // kill函数原型： int kill(pid_t pid,int signo)
    // pid > 0：将信号发送给进程 ID 为 pid 的进程。
    // pid ==0：将信号发送给与发送进程属于同一进程组的所有进程。
    // pid < 0：将信号发送给进程组 ID 等于 pid 的绝对值的所有进程。
    // pid ==-1：将信号发送给系统中所有进程。
    if (!strcmp(argv[0], "bg")) // 该进程需要在后台运行
    {
        // bg会启动子进程，并将其放置于后台执行
        job->state = BG;                  // 设置状态BG
        if (kill(-job->pid, SIGCONT) < 0) // 采用负数发送信号到进程组
            unix_error("kill error");
        printf("[%d] (%d) %s", job->jid, job->pid, job->cmdline);
    }
    else if (!strcmp(argv[0], "fg")) // 该进程需要在前台运行
    {
        job->state = FG;                  // 设置状态FG
        if (kill(-job->pid, SIGCONT) < 0) // 采用负数发送信号到进程组
            unix_error("kill error");
        // 当一个进程被设置为前台执行时，当前tsh应该等待该子进程结束
        waitfg(job->pid);
    }
    else // 指令出现异常
    {
        puts("do_bgfg: Internal error");
        exit(0);
    }
    return;
}

/*
 * waitfg - Block until process pid is no longer the foreground process
 */
void waitfg(pid_t pid)
{
    // 通过pid获取该pid对应的job本体
    struct job_t *job = getjobpid(jobs, pid);
    if (!job)
        return;

    // 新设立一个wait信号集
    sigset_t wait;
    if (sigemptyset(&wait) < 0) // 清空wait信号集，该信号集为空
        unix_error("sigemptyset &wait error");

    // sigsuspend函数原型： int sigsuspend(const sigset_t *mask);
    // 用于在接收到某个信号之前，临时用mask替换进程的信号掩码，并暂停进程执行，直到收到信号为止

    //   如果当前子进程的状态没有发生改变，则tsh继续休眠
    while (job->state == FG)
        // 一旦有信号改变，就判定是否
        sigsuspend(&wait); // 使用空信号集替换信号掩码，即信号掩码为空，此时任何信号都会唤醒该进程

    return;
}

/*****************
 * Signal handlers
 *****************/

/*
 * sigchld_handler- 处理僵尸子进程例程
 每当子作业终止（变成僵尸），或者因为接收到SIGSTOP或SIGTSTP信号而停止时，内核都会向shell发送sigchld。处理程序获取所有可用的僵尸子进程，但不等待任何其他当前正在运行的子进程终止。
 */
void sigchld_handler(int sig)
{
    int status, jid;
    pid_t pid;
    struct job_t *job;

    if (verbose)
        puts("sigchld_handler: entering"); // 输出额外信息

    /*
    waitpid函数原型： pid_t waitpid(pid_t pid , int *status , int options)
    总体：
    如果没有子进程或其它错误原因，则返回-1；
    如果成功回收子进程，则返回回收的那个子进程的ID；
    如果第三个参数为WNOHANG，且子进程都在运行，则返回0
    参数：
    pid：从参数的名字上可以看出来这是一个进程的ID。但是这里pid的值不同时，会有不同的意义。
        1.pid > 0时，只等待进程ID等于pid的子进程，只要该子进程不结束，就会一直等待下去；
        2.pid = -1时，等待任何一个子进程的退出，此时作用和wait相同；
        3.pid = 0时，等待同一个进程组中的任何子进程；
        4.pid < -1时，等待一个指定进程组中的任何子进程，这个进程组的ID等于pid的绝对值。
    options:options提供了一些额外的选项来控制waitpid
        WNOHANG   : 若子进程仍然在运行，则返回0
        （注意只有设置了这个标志，waitpid才有可能返回0）
        WUNTRACED : 如果子进程由于传递信号而停止，则马上返回。
        （只有设置了这个标志，waitpid返回时，其WIFSTOPPED(status)才有可能返回true）
    &status参数：
        WIFEXITED(status)
        如果正常退出（exit）返回非零值；这时可以用WEXITSTATUS(status) 得到退出编号（exit的参数）
        WIFSIGNALED(status)
        如果异常退出 （子进程接受到退出信号） 返回非零值；使用WTERMSIG (status) 得到使子进程退出得信号编号
        WIFSTOPPED(status)
        如果是暂停进程返回的状态，返回非零值；使用WSTOPSIG（status） 得到使子进程暂停得信号编号
    */

    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) // 以非阻塞方式等待所有子进程，若成功回收了子进程，则返回这个子进程的PID，&status中返回其状态
    {

        // 如果当前这个子进程的job已经删除了，则表示有错误发生
        if ((job = getjobpid(jobs, pid)) == NULL)
        {
            printf("Lost track of (%d)\n", pid);
            return;
        }

        jid = job->jid;
        // 接下来判断三种状态
        //  如果这个子进程收到了一个暂停信号（还没退出）
        if (WIFSTOPPED(status))
        {
            printf("Job [%d] (%d) stopped by signal %d\n", jid, job->pid, WSTOPSIG(status));
            // 使用WSTOPSIG（status） 得到使子进程暂停得信号编号
            job->state = ST; // 状态设为挂起
        }
        // 如果子进程通过调用 exit 或者一个返回 (return) 正常终止
        else if (WIFEXITED(status))
        {
            if (deletejob(jobs, pid))
                if (verbose)
                {
                    printf("sigchld_handler: Job [%d] (%d) deleted\n", jid, pid);
                    printf("sigchld_handler: Job [%d] (%d) terminates OK (status %d)\n", jid, pid, WEXITSTATUS(status));
                    // 用WEXITSTATUS(status) 得到退出编号（exit的参数）
                }
        }
        // 如果子进程是因为一个未被捕获的信号终止的，例如SIGKILL
        else
        {
            if (deletejob(jobs, pid))
            { // 清除进程
                if (verbose)
                    printf("sigchld_handler: Job [%d] (%d) deleted\n", jid, pid);
            }
            printf("Job [%d] (%d) terminated by signal %d\n", jid, pid, WTERMSIG(status));
            // 使用WTERMSIG (status) 得到使子进程退出得信号编号
        }
    }

    if (verbose)
        puts("sigchld_handler: exiting");

    return;
}

/*
 * sigint_handler - 当用户在键盘上键入ctrl-c时，内核会向shell发送一个SIGINT。抓住它并将其发送到前台作业。
 */
void sigint_handler(int sig)
{
    if (verbose)
        puts("sigint_handler: entering");
    pid_t pid = fgpid(jobs); // 获取前台进程的pid

    if (pid)
    {
        // 发送SIGINT给前台进程组里的所有进程
        // 需要注意的是，前台进程组内的进程除了当前前台进程以外，还包括前台进程的子进程。
        // 最多只能存在一个前台进程，但前台进程组内可以存在多个进程
        if (kill(-pid, SIGINT) < 0) // 采用负数发送信号到进程组，使该进程终止
            unix_error("kill (sigint) error");
        if (verbose)
        {
            printf("sigint_handler: Job (%d) killed\n", pid);
        }
    }
    if (verbose)
        puts("sigint_handler: exiting");
    return;
}

/*
 * sigtstp_handler - 每当用户在键盘上键入ctrl-z时，内核都会向shell发送一个sigtstp。捕获它并通过向它发送SIGTSTP来挂起前台作业。
 */
void sigtstp_handler(int sig)
{
    if (verbose)
        puts("sigstp_handler: entering");

    pid_t pid = fgpid(jobs);                  // 获取前台进程的pid号
    struct job_t *job = getjobpid(jobs, pid); // 获取前台进程的job本体

    if (pid)

        if (kill(-pid, SIGTSTP) < 0) // 采用负数发送信号到进程组，使该进程挂起
            unix_error("kill (tstp) error");
    if (verbose)
    {
        printf("sigstp_handler: Job [%d] (%d) stopped\n", job->jid, pid);
    }

    if (verbose)
        puts("sigstp_handler: exiting");
    return;
}

/*********************
 * End signal handlers
 *********************/

/***********************************************
 * Helper routines that manipulate the job list
 **********************************************/

/* clearjob - Clear the entries in a job struct */
void clearjob(struct job_t *job)
{
    job->pid = 0;
    job->jid = 0;
    job->state = UNDEF;
    job->cmdline[0] = '\0';
}

/* initjobs - Initialize the job list */
void initjobs(struct job_t *jobs)
{
    int i;

    for (i = 0; i < MAXJOBS; i++)
        clearjob(&jobs[i]);
}

/* maxjid - Returns largest allocated job ID */
int maxjid(struct job_t *jobs)
{
    int i, max = 0;

    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].jid > max)
            max = jobs[i].jid;
    return max;
}

/* addjob - Add a job to the job list */
int addjob(struct job_t *jobs, pid_t pid, int state, char *cmdline)
{
    int i;

    if (pid < 1)
        return 0;

    for (i = 0; i < MAXJOBS; i++)
    {
        if (jobs[i].pid == 0)
        {
            jobs[i].pid = pid;
            jobs[i].state = state;
            jobs[i].jid = nextjid++;
            if (nextjid > MAXJOBS)
                nextjid = 1;
            strcpy(jobs[i].cmdline, cmdline);
            if (verbose)
            {
                printf("Added job [%d] %d %s\n", jobs[i].jid, jobs[i].pid, jobs[i].cmdline);
            }
            return 1;
        }
    }
    printf("Tried to create too many jobs\n");
    return 0;
}

/* deletejob - Delete a job whose PID=pid from the job list */
int deletejob(struct job_t *jobs, pid_t pid)
{
    int i;

    if (pid < 1)
        return 0;

    for (i = 0; i < MAXJOBS; i++)
    {
        if (jobs[i].pid == pid)
        {
            clearjob(&jobs[i]);
            nextjid = maxjid(jobs) + 1;
            return 1;
        }
    }
    return 0;
}

/* fgpid - Return PID of current foreground job, 0 if no such job */
pid_t fgpid(struct job_t *jobs)
{
    int i;

    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].state == FG)
            return jobs[i].pid;
    return 0;
}

/* getjobpid  - Find a job (by PID) on the job list */
struct job_t *getjobpid(struct job_t *jobs, pid_t pid)
{
    int i;

    if (pid < 1)
        return NULL;
    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].pid == pid)
            return &jobs[i];
    return NULL;
}

/* getjobjid  - Find a job (by JID) on the job list */
struct job_t *getjobjid(struct job_t *jobs, int jid)
{
    int i;

    if (jid < 1)
        return NULL;
    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].jid == jid)
            return &jobs[i];
    return NULL;
}

/* pid2jid - Map process ID to job ID */
int pid2jid(pid_t pid)
{
    int i;

    if (pid < 1)
        return 0;
    for (i = 0; i < MAXJOBS; i++)
        if (jobs[i].pid == pid)
        {
            return jobs[i].jid;
        }
    return 0;
}

/* listjobs - Print the job list */
void listjobs(struct job_t *jobs)
{
    int i;

    for (i = 0; i < MAXJOBS; i++)
    {
        if (jobs[i].pid != 0)
        {
            printf("[%d] (%d) ", jobs[i].jid, jobs[i].pid);
            switch (jobs[i].state)
            {
            case BG:
                printf("Running ");
                break;
            case FG:
                printf("Foreground ");
                break;
            case ST:
                printf("Stopped ");
                break;
            default:
                printf("listjobs: Internal error: job[%d].state=%d ", i, jobs[i].state);
            }
            printf("%s", jobs[i].cmdline);
        }
    }
}
/******************************
 * end job list helper routines
 ******************************/

/***********************
 * Other helper routines
 ***********************/

/*
 * usage - print a help message
 */
void usage(void)
{
    printf("Usage: shell [-hvp]\n");
    printf("   -h   print this message\n");
    printf("   -v   print additional diagnostic information\n");
    printf("   -p   do not emit a command prompt\n");
    exit(1);
}

/*
 * unix_error - unix-style error routine
 */
void unix_error(char *msg)
{
    fprintf(stdout, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

/*
 * app_error - application-style error routine
 */
void app_error(char *msg)
{
    fprintf(stdout, "%s\n", msg);
    exit(1);
}

/*
 * Signal - wrapper for the sigaction function
 */
handler_t *Signal(int signum, handler_t *handler)
{
    struct sigaction action, old_action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask); /* block sigs of type being handled */
    action.sa_flags = SA_RESTART; /* restart syscalls if possible */

    if (sigaction(signum, &action, &old_action) < 0)
        unix_error("Signal error");
    return (old_action.sa_handler);
}

/*
 * sigquit_handler - The driver program can gracefully terminate the
 *    child shell by sending it a SIGQUIT signal.
 */
void sigquit_handler(int sig)
{
    printf("Terminating after receipt of SIGQUIT signal\n");
    exit(1);
}
