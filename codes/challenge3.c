#include <stdlib.h>
#include <stdio.h>

#include "rave_user_events.h"
/*
//original code
void transpose(int N, int M, double A[N][M], double B[N][M], double alpha){
    rave_event_and_value(1000,1);
    for(int i=0; i<N; ++i){
        for(int j=0; j<M; ++j){
            A[i][j] = B[j][i] * alpha;
        }
    }
    rave_event_and_value(1000,0);
}
*/

// my modification
void transpose(int N, int M, double A[N][M], double B[N][M], double alpha)
{
   rave_event_and_value(1000, 1);
   // the point here is to change N<-->M
   // because the compiler vectorize filling the avg_VL
   // N has more data so we fill the avg_VL
   // if we use M to fill the avg_VL we only have 8 elements
   // so we dont fill the avg_VL
   for (int i = 0; i < M; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         A[i][j] = B[j][i] * alpha;
      }
   }
   rave_event_and_value(1000, 0);
}

// Don't touch the main function!
int main()
{
   rave_name_event(1000, "code_region");
   rave_name_value(1000, 0, "Other");
   rave_name_value(1000, 1, "Transpose");

   int N = 4096;
   int M = 8;

   double A[N][M];
   double B[N][M];

   transpose(N, M, A, B, 42.0);

   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < M; ++j)
      {
         if (A[i][j] != B[j][i] * 42.0)
         {
            printf("Incorrect result!");
            exit(-1);
         }
      }
   }
   printf("Correct!\n");
}