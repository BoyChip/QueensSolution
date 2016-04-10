#include "solution_queens.h"

solution_queens::solution_queens()
{
    fp = fopen("number_queen.txt","r");
    fscanf(fp, "%d",&N);
    fclose(fp);

    results = 0;
    D = 2*N - 1;
    SG = N - 1;
}

void solution_queens::try_row(int i)
{
    for (int j = 0; j < N; j++){
     if (A[j] && B[i - j + SG] && C[i + j]) {
      result[i] = j;
      A[j] = FALSE;
      B[i - j + SG] = FALSE;
      C[i + j] = FALSE;
      if (i == N - 1){
       results++;
       print_result(result);
      }
      else
        try_row(i + 1);
        A[j] = TRUE;
        B[i - j + SG] = TRUE;
        C[i + j] = TRUE;
     }
   }
}

void solution_queens::print_result(int *result)
{
    for (int j = 0; j < N; j++){
       fprintf(fp,"%d ", result[j]);
    }
    fprintf(fp,"\n");
    results = results;
}

void solution_queens::run()
{
    fp = fopen("result.txt", "w");
    for (int i = 0; i < N; i++)
        A[i] = TRUE;
    for (int i = 0; i < D; i++){
        B[i] = TRUE;
        C[i] = TRUE;
    }
    try_row(0);
    fclose(fp);
    fp = fopen("total_result.txt","w");
    fprintf(fp, "%d", results);
    fclose(fp);
}
