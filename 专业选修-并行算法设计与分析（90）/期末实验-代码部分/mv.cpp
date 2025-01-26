#include "algorithm"
#include "fstream"
#include "iostream"
#include "omp.h"
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

int num_thread = 2;

typedef struct
{
    int n_rows;    // 矩阵的行数
    int n_cols;    // 矩阵的列数
    int n_nonzero; // 非零元素的个数
    int *row_ptr;  // 行指针数组
    int *col_ind;  // 列索引数组
    double *val;   // 非零元素值数组
} crs_matrix_t;

// 读入稀疏矩阵
crs_matrix_t read_mtx_file(const char *filename)
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    // 跳过第一行的说明信息
    char line[256];
    if (fgets(line, sizeof(line), f) == NULL)
    {
        fprintf(stderr, "Error reading file header\n");
        fclose(f);
        exit(1);
    }

    // 读取矩阵的基本信息
    int n_rows, n_cols, n_nonzero;
    if (fscanf(f, "%d %d %d", &n_rows, &n_cols, &n_nonzero) != 3)
    {
        fprintf(stderr, "Error reading matrix dimensions\n");
        fclose(f);
        exit(1);
    }
    // cout << n_rows << " " << n_cols << " " << n_nonzero;

    // 分配内存
    crs_matrix_t A;
    A.n_rows = n_rows;
    A.n_cols = n_cols;
    A.n_nonzero = n_nonzero;
    A.row_ptr = (int *)malloc((n_rows + 1) * sizeof(int));
    A.col_ind = (int *)malloc(n_nonzero * sizeof(int));
    A.val = (double *)malloc(n_nonzero * sizeof(double));

    // 读取非零元素的行索引、列索引和值
    int row = 0, idx = 0;
    A.row_ptr[0] = 0;
    for (int i = 0; i < n_nonzero; i++)
    {
        int r, c;
        double v;
        if (fscanf(f, "%d %d %le", &r, &c, &v) != 3)
        {
            fprintf(stderr, "Error reading matrix element\n");
            fclose(f);
            free(A.row_ptr);
            free(A.col_ind);
            free(A.val);
            exit(1);
        }
        A.col_ind[i] = c - 1; // 存储列索引（减1）
        A.val[i] = v;         // 存储值
        while (r > row + 1)
        {
            A.row_ptr[row + 1] = i;
            row++;
        }
        row = r - 1;
    }
    while (row < n_rows)
    {
        A.row_ptr[row + 1] = n_nonzero;
        row++;
    }

    fclose(f);
    return A;
}

// 输出稀疏矩阵参数
void print_matrix_par(const crs_matrix_t *A)
{
    // data
    cout << " data:      ";
    for (int i = 0; i < A->n_nonzero; i++)
    {
        cout << A->val[i] << " ";
    }
    cout << endl;
    // col
    cout << " col index: ";
    for (int i = 0; i < A->n_nonzero; i++)
    {
        cout << A->col_ind[i] << " ";
    }
    cout << endl;
    // row
    cout << " row ptr:   ";
    for (int i = 0; i < A->n_rows + 1; i++)
    {
        cout << A->row_ptr[i] << " ";
    }
    cout << endl;
}

// 打印部分矩阵
void print_matrix_head(const crs_matrix_t *A, int rows, int cols)
{
    printf("Printing the first %d x %d elements of the matrix:\n", rows, cols);
    // 打开一个新的输出文件
    std::ofstream outFile("output.txt");

    // 检查文件是否打开成功
    if (outFile.is_open())
    {
        // 将输出写入文件
        for (int i = 0; i < rows; i++)
        {
            double *temp_row = new double[A->n_cols]; // 临时数组，逐行输出
            for (int j = 0; j < cols; j++)
                temp_row[j] = 0;
            for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++) // j为该数在data中的位置
            {
                if (A->col_ind[j] < cols) // A->col_ind[j]为该数的列号，i为该数的行号
                {
                    temp_row[A->col_ind[j]] = A->val[j];
                }
            }
            for (int j = 0; j < cols; j++)
                printf("%20.8f", temp_row[j]);
            printf("\n");
        }

        // 关闭文件
        outFile.close();

        std::cout << "Output written to 'output.txt'." << std::endl;
    }
    else
    {
        std::cerr << "Unable to open output file." << std::endl;
        return;
    }

    // for (int i = 0; i < rows; i++)
    // {
    //     double *temp_row = new double[A->n_cols]; // 临时数组，逐行输出
    //     for (int j = 0; j < cols; j++)
    //         temp_row[j] = 0;
    //     for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++) // j为该数在data中的位置
    //     {
    //         if (A->col_ind[j] < cols) // A->col_ind[j]为该数的列号，i为该数的行号
    //         {
    //             temp_row[A->col_ind[j]] = A->val[j];
    //         }
    //     }
    //     for (int j = 0; j < cols; j++)
    //         printf("%20.8f", temp_row[j]);
    //     printf("\n");
    // }
}

// 生成随机向量
double *generate_random_vector(int n, double min, double max)
{
    double *vec = (double *)malloc(n * sizeof(double));
    // 初始化随机数种子
    srand(time(NULL));
    // cout << "random vec: ";
    for (int i = 0; i < n; i++)
    {
        vec[i] = min + (double)rand() / RAND_MAX * (max - min);
        // cout << vec[i] << " ";
    }
    // cout << endl;

    return vec;
}

// 矩阵向量乘法(串行)
void crs_matrix_vector_product_serial(const crs_matrix_t *A, double *x, double *y)
{
    for (int i = 0; i < A->n_rows; i++)
    {
        double sum = 0.0;
        for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++)
        {
            sum += A->val[j] * x[A->col_ind[j]];
        }
        y[i] = sum;
    }
}

// 矩阵向量乘法(并行化外层循环)
void crs_matrix_vector_product_parallel(const crs_matrix_t *A, double *x, double *y)
{
    omp_set_num_threads(num_thread);
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < A->n_rows; i++)
    {
        double sum = 0.0;
        for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++)
        {
            sum += A->val[j] * x[A->col_ind[j]];
        }
        y[i] = sum;
        // cout << "i= " << i << " " << omp_get_thread_num() << "    ";
        // if (i % 10 == 0) cout << endl;
    }
}

// 矩阵向量乘法(并行化外层循环+动态调度)
void crs_matrix_vector_product_parallel2(const crs_matrix_t *A, double *x, double *y)
{
    omp_set_num_threads(num_thread);
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < A->n_rows; i++)
    {
        double sum = 0.0;
        for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++)
        {
            sum += A->val[j] * x[A->col_ind[j]];
        }
        y[i] = sum;
        // cout << "i= " << i << " " << omp_get_thread_num() << "    ";
        // if (i % 10 == 0) cout << endl;
    }
}

// 矩阵向量乘法(并行化外层循环+动态调度+内层并行)
void crs_matrix_vector_product_parallel3(const crs_matrix_t *A, double *x, double *y)
{
    omp_set_num_threads(num_thread);
#pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < A->n_rows; i++)
    {
        double sum = 0.0;
#pragma omp parallel for schedule(dynamic) reduction(+ : sum)
        for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++)
        {
            sum += A->val[j] * x[A->col_ind[j]];
        }
        y[i] = sum;
    }
}

// 矩阵向量乘法（私有临时x向量）
void crs_matrix_vector_product_parallel4(const crs_matrix_t *A, double *x, double *y)
{
    omp_set_num_threads(num_thread);
#pragma omp parallel
    {
        // 声明线程私有的临时 x 向量
        double private_x[A->n_cols];
        for (int i = 0; i < A->n_cols; i++)
        {
            // 将 x 向量拷贝到线程私有的缓存中
            private_x[i] = x[i];
        }

#pragma omp for
        for (int i = 0; i < A->n_rows; i++)
        {
            double sum = 0.0;
            for (int j = A->row_ptr[i]; j < A->row_ptr[i + 1]; j++)
            {
                // 使用线程私有的 private_x 向量进行计算
                sum += A->val[j] * private_x[A->col_ind[j]];
            }
            y[i] = sum;
        }
    }
}

// 比较函数（比较串并行结果是否一致）
void compare(double *x, double *y, int size, string name)
{
    bool flag = true;
    int wrong_num = 0;
    for (int i = 0; i < size; i++)
    {
        if (x[i] != y[i])
        {
            flag = false;
            wrong_num++;
        }
    }
    cout << name << "  accuracy: " << (double)(size - wrong_num) / (double)size << "      ";
    if (flag == true)
        cout << "(outcome accurate)" << endl;
    else
        cout << "(outcome wrong)" << endl;
}

int main(int argc, char *argv[])
{
    // 读取参数，确定线程数
    string matrix_name;
    if (argc < 3)
    {
        std::cout << "Usage: " << argv[0] << " <thread_num> <matrix_name>\n";
        return 1;
    }
    try
    {
        num_thread = std::stoi(argv[1]);
        std::cout << "set thread number : " << num_thread << std::endl;
        matrix_name = argv[2];
        std::cout << "set matrix name   : " << matrix_name << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << " - Invalid argument: " << argv[1] << std::endl;
        return 1;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: " << e.what() << " - Argument " << argv[1] << " is out of range" << std::endl;
        return 1;
    }

    // 检测环境
    int concurrency = omp_get_num_procs();
    cout << "system max concurrency = " << concurrency << endl;
    //
    const char *filename = "psmigr_3_line.mtx"; // default
    string file_e = matrix_name + "_line.mtx";
    filename = file_e.c_str();
    crs_matrix_t A = read_mtx_file(filename);
    // print_matrix_par(&A);
    // print_matrix_head(&A, 5, 4);

    double *v = generate_random_vector(A.n_cols, 1, 1);
    double *ans_serial = new double[A.n_cols];
    double *ans_parallel = new double[A.n_cols];
    double *ans_parallel2 = new double[A.n_cols];
    double *ans_parallel3 = new double[A.n_cols];

    // 串行计算
    auto start_serial = std::chrono::high_resolution_clock::now();
    crs_matrix_vector_product_serial(&A, v, ans_serial);
    auto end_serial = std::chrono::high_resolution_clock::now();
    // cout << "ans = " << endl;
    // for (int i = 0; i < A.n_rows; i++)
    //     cout << ans_serial[i] << " ";
    // cout << endl;

    // 并行计算(优化外层循环)
    auto start_parallel = std::chrono::high_resolution_clock::now();
    crs_matrix_vector_product_parallel(&A, v, ans_parallel);
    auto end_parallel = std::chrono::high_resolution_clock::now();

    // 并行计算（优化外层循环+动态调度）
    auto start_parallel2 = std::chrono::high_resolution_clock::now();
    crs_matrix_vector_product_parallel2(&A, v, ans_parallel2);
    auto end_parallel2 = std::chrono::high_resolution_clock::now();

    // 并行计算（优化外层循环+动态调度+内层并行）
    auto start_parallel3 = std::chrono::high_resolution_clock::now();
    crs_matrix_vector_product_parallel3(&A, v, ans_parallel3);
    auto end_parallel3 = std::chrono::high_resolution_clock::now();

    // 比较准确性
    compare(ans_serial, ans_parallel, A.n_cols, "parallel-basic");
    compare(ans_serial, ans_parallel2, A.n_cols, "parallel-2");
    compare(ans_serial, ans_parallel3, A.n_cols, "parallel-3");

    // 比较性能
    std::chrono::duration<double, std::milli> duration_serial = end_serial - start_serial;
    std::chrono::duration<double, std::milli> duration_parallel = end_parallel - start_parallel;
    std::chrono::duration<double, std::milli> duration_parallel2 = end_parallel2 - start_parallel2;
    std::chrono::duration<double, std::milli> duration_parallel3 = end_parallel3 - start_parallel3;
    cout << "serial time   =" << duration_serial.count() << "ms" << endl
         << endl;
    cout << "parallel time =" << duration_parallel.count() << "ms" << endl;
    cout << "speedup1      =" << duration_serial.count() / duration_parallel.count() << endl
         << endl;
    cout << "parallel time2=" << duration_parallel2.count() << "ms" << endl;
    cout << "speedup2      =" << duration_serial.count() / duration_parallel2.count() << endl
         << endl;
    cout << "parallel time3=" << duration_parallel3.count() << "ms" << endl;
    cout << "speedup3      =" << duration_serial.count() / duration_parallel3.count() << endl;

    //  释放内存
    free(A.row_ptr);
    free(A.col_ind);
    free(A.val);
    return 0;
}
