#ifndef SOLUTION_QUEENS_H
#define SOLUTION_QUEENS_H


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX 13

class solution_queens
{
public:
    solution_queens();
    int N;
    int A[MAX];
    int B[MAX*2];
    int C[MAX*2];

    int SG;
    int D;
    int result[MAX];
    int results;

    FILE *fp;
    void try_row(int i);
    void print_result(int *result);
    void run();

};

#endif // SOLUTION_QUEENS_H
