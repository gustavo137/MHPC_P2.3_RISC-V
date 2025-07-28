#include <stdlib.h>
#include <stdio.h>

#include "rave_user_events.h"

/*
// origional code
void axpy_2d(int N, int M, double X[N][M], double Y[N][M], double alpha)
{
   rave_event_and_value(1000, 1);
   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < M; ++j)
      {
         Y[i][j] += X[i][j] * alpha;
      }
   }
   rave_event_and_value(1000, 0);
}
*/

// my modification
void axpy_2d(int N, int M, double X[N][M], double Y[N][M], double alpha)
{
   // remember that we only check the loops
   //  we transform 2D vector to 1D vectors and
   //  we only use a single loop
   double *X_ptr = &X[0][0];
   double *Y_ptr = &Y[0][0];
   rave_event_and_value(1000, 1);
   for (int ij = 0; ij < N * M; ij++)
   {
      Y_ptr[ij] += X_ptr[ij] * alpha;
   }
   // for(int i=0; i<N; ++i){
   // for(int j=0; j<M; ++j){
   // Y[i][j] += X[i][j] * alpha;//original
   //}
   //}
   rave_event_and_value(1000, 0);
}

// Don't touch the main function!
int main()
{
   rave_name_event(1000, "code_region");
   rave_name_value(1000, 0, "Other");
   rave_name_value(1000, 1, "Transpose");

   int N = 64;
   int M = 64;

   double X[N][M];
   double Y[N][M];
   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < M; ++j)
      {
         X[i][j] = 11.0;
         Y[i][j] = 33.0;
      }
   }

   axpy_2d(N, M, X, Y, 42.0);

   for (int i = 0; i < N; ++i)
   {
      for (int j = 0; j < M; ++j)
      {
         double diff = Y[i][j] - (33.0 + 11.0 * 42.0);
         if (diff * diff > 1e-3)
         {
            printf("Incorrect result!");
            exit(-1);
         }
      }
   }
   printf("Correct!\n");
}