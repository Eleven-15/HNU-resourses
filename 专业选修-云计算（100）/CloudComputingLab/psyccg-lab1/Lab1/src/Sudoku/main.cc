#include <assert.h>
#include <chrono>
#include <iostream>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/time.h>
#include <thread>
#include <unistd.h> //sleep
#include <vector>

#include "ThreadPool.h"
#include "sudoku.h"

int numOfWorkerThread = 1;
char ans_puzzle[buffer_size + 10][N + 1];
bool answer_flag[buffer_size + 10];

void *print_answer(void *args)
{
    int i = 0; // num to print now
    while (true)
    {
        usleep(0.0001);
        if (TEST_R)
            printf("print thread wake up\n");
        // printf("bbb: %d\n", answer_flag[i]);
        if (answer_flag[i])
        {
            if (DEBUG)
                printf("ans: ");
            for (int j = 0; j < N; j++)
                printf("%c", ans_puzzle[i][j]);
            printf("\n");
            answer_flag[i] = 0;
            i++;
            if (i == buffer_size)
                i -= buffer_size;
        }
    }
}

int main(int argc, char *argv[])
{
    char puzzle[N + 1];
    const int concurrency = std::thread::hardware_concurrency(); // cpu内核数量
    numOfWorkerThread = concurrency * 2;
    if (DEBUG || TEST_R)
        printf("numOfWorkerThread= %d\n", numOfWorkerThread);
    ThreadPool pool(numOfWorkerThread);
    std::vector<std::future<int>> results;
    // initial
    memset(answer_flag, 0, sizeof(answer_flag));
    // 创建输出线程
    pthread_t th;
    if (pthread_create(&th, NULL, print_answer, NULL) != 0)
    {
        perror("output pthread_create failed");
        exit(1);
    }

    // 主进程等待在输入流
    char *str;
    str = (char *)malloc(100 * sizeof(char));
    int line_num = 0;
    while (true)
    {
        if (scanf("%s", str) != 1)
        {
            printf("ERROR:command not read\n");
        };
        // quit
        if (strcmp(str, "quit") == 0)
        {
            break;
        }
        // 打开文件
        FILE *fp = fopen(str, "r");
        if (fp == nullptr)
        {
            // 文件打开失败
            printf("ERROR:file not open\n");
        }
        else
        {
            // 文件打开成功
            while (fgets(puzzle, sizeof puzzle, fp) != NULL)
            {
                if (strlen(puzzle) >= N)
                {
                    results.emplace_back(
                        pool.enqueue([line_num, puzzle]
                                     {
                            // pthread_t tid = pthread_self();
                            if (DEBUG || TEST_R) printf("thread [%d] start\n", line_num);
                            if (DEBUG) printf("get: ");
                            if (DEBUG) for (int i = 0; i < N; i++) printf("%c", puzzle[i]);
                            if (DEBUG) printf("\n");

                            // excute
                            // char p[N + 1];
                            // for (int i = 0; i < N; i++)
                            //     p[i] = puzzle[i] + 1;
                            // p[N] = '\0';

                            // 使用output输出，多线程要在这里考虑输出顺序
                            struct answer answer = one_solve(puzzle);
                            if (DEBUG) for (int i = 0; i < N; i++) printf("%c", answer.ans[i]);
                            if (DEBUG) printf("\n");
                            strcpy(ans_puzzle[line_num], answer.ans);

                            if (DEBUG || TEST_R) printf("thread [%d] end\n", line_num);
                            answer_flag[line_num] = 1;
                            //printf("aaa: %d\n",answer_flag[line_num]);
                            return line_num; }));
                    if (DEBUG)
                        for (int j = 0; j < N; j++)
                            printf("%c", puzzle[j]);
                    if (DEBUG)
                        printf("\n");
                    line_num++;
                    if (line_num == buffer_size)
                        line_num -= buffer_size;
                }
            }
        }
        fclose(fp);
    }
    return 0;
}
