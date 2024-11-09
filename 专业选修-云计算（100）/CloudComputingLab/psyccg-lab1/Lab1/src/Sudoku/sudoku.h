#ifndef SUDOKU_H
#define SUDOKU_H

#define DEBUG 0
#define TEST_R 0
#include <string.h>

const bool DEBUG_MODE = false;
enum
{
    ROW = 9,
    COL = 9,
    N = 81,
    NEIGHBOR = 20
};
const int NUM = 9;
const int buffer_size = 1e6; // 1e6

extern bool answer_flag[buffer_size + 10];
extern char answer_print[buffer_size + 10][N + 1];
extern int numOfWorkerThread;

struct answer
{
    char ans[N + 1];
    answer(char *answer)
    {
        strcpy(ans, answer);
    }
};

struct answer one_solve(const char *puzzle);
void print(char answer[]);

#endif
