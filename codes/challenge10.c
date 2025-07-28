#include <stdlib.h>
#include <stdio.h>

#include "rave_user_events.h"

void inner_outer(int N, int M, double *Y, double *X, double *S)
{
   rave_event_and_value(1000, 1);
   for (int i = 0; i < N; ++i)
   {
      double sub = 0;
      for (int j = 0; j < M; ++j)
      {
         sub -= X[j] * Y[i];
      }
      Y[i] *= S[i];
      Y[i] *= sub;
   }
   rave_event_and_value(1000, 0);
}

// Don't touch the main function!
int main()
{
   rave_name_event(1000, "code_region");
   rave_name_value(1000, 0, "Other");
   rave_name_value(1000, 1, "Reduction");
   rave_name_value(1000, 2, "Reduction_outer");

   int N = 512;
   int M = 512;

   double *X = (double *)malloc(sizeof(double) * M);
   double *Y = (double *)malloc(sizeof(double) * N);
   double *S = (double *)malloc(sizeof(double) * N);

#pragma clang loop vectorize(disable)
   for (int i = 0; i < N; ++i)
   {
      X[i] = (double)i;
   }
#pragma clang loop vectorize(disable)
   for (int i = 0; i < N; ++i)
   {
      Y[i] = 42.0;
      S[i] = i * 2.0;
   }

   inner_outer(N, M, Y, X, S);

   for (int i = 0; i < N; i++)
   {
      double res = 0;
      for (int j = 0; j < M; ++j)
      {
         res -= X[j] * 42.0;
      }
      res *= 42.0 * S[i];
      double diff = Y[i] - res;
      if (diff * diff > 1e-3)
      {
         printf("Incorrect result!\n");
         exit(-1);
      }
   }
   printf("Correct!\n");

   return 0;
}
