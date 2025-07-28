#include <stdlib.h>
#include <stdio.h>

#include "rave_user_events.h"

void foo(int N, int M, int ZVECD, double condition[ZVECD], double A[M][N], double E[N][M][ZVECD])
{
   rave_event_and_value(1000, 1);
   for (int z = 0; z < ZVECD; ++z)
   {
      if (condition[z] > 0.5)
      {
         for (int m = 0; m < M; ++m)
         {
            for (int n = 0; n < N; ++n)
            {
               A[m][n] = A[m][n] + E[n][m][z];
            }
         }
      }
   }
   rave_event_and_value(1000, 0);
}

// Don't touch the main function!
int main()
{
   rave_name_event(1000, "code_region");
   rave_name_value(1000, 0, "Other");
   rave_name_value(1000, 1, "foo");

   int N = 4;
   int M = 8;
   int ZVECD = 1024;
   double A[M][N];
   double condition[ZVECD];
   double E[N][M][ZVECD];

   double golden[M][N];
   for (int i = 0; i < M; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         A[i][j] = (double)(i * j);
         golden[i][j] = (double)(i * j);
#pragma clang loop vectorize(disable)
         for (int z = 0; z < ZVECD; ++z)
         {
            E[j][i][z] = (double)(i * j + z);
            if (i == 0 & j == 0)
               condition[z] = z % 2 ? 0.25 : 0.75;
         }
      }
   }

   foo(N, M, ZVECD, condition, A, E);

   // Check result
   for (int z = 0; z < ZVECD; ++z)
   {
      if (condition[z] > 0.5)
      {
         for (int m = 0; m < M; ++m)
         {
            for (int n = 0; n < N; ++n)
            {
               golden[m][n] = golden[m][n] + E[n][m][z];
            }
         }
      }
   }
   for (int m = 0; m < M; ++m)
   {
      for (int n = 0; n < N; ++n)
      {
         double diff = A[m][n] - golden[m][n];
         if (diff * diff > 1e-3)
         {
            printf("Incorrect result!\n");
            exit(-1);
         }
      }
   }
   printf("Correct!\n");
}
