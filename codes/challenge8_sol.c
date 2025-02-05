#include <stdlib.h>
#include <stdio.h>

#include "rave_user_events.h"

void halfwork(int N, double *A, double *B, double alpha, double *R1, double *R2)
{
   rave_event_and_value(1000, 1);
   for (int i = 0; i < N; ++i)
   {
      R1[i] = A[i] * alpha;
   }
   for (int i = 0; i < N / 2; ++i)
   {
      R2[i] = (B[2 * i] + B[2 * i + 1]) / 2.0;
   }
   rave_event_and_value(1000, 0);
}

// Don't touch the main function!
int main()
{
   rave_name_event(1000, "code_region");
   rave_name_value(1000, 0, "Other");
   rave_name_value(1000, 1, "Halfwork");

   int N = 1024;
   int N2 = N / 2;

   double *A = (double *)malloc(sizeof(double) * N);
   double *B = (double *)malloc(sizeof(double) * N);
   double *R1 = (double *)malloc(sizeof(double) * N);
   double *R2 = (double *)malloc(sizeof(double) * N2);
#pragma clang loop vectorize(disable)
   for (int i = 0; i < N; ++i)
   {
      A[i] = (double)i;
      B[i] = (double)32.0;
      R1[i] = 0;
      R2[i] = 0;
   }

   halfwork(N, A, B, 42.0, R1, R2);

   for (int i = 0; i < N; ++i)
   {
      double diff = R1[i] - (A[i] * 42.0);
      if (i < N / 2)
         diff += R2[i] - (B[2 * i] + B[2 * i + 1]) / 2.0;
      if (diff * diff > 1e-3)
      {
         printf("Incorrect Result!\n");
         exit(-1);
      }
   }
   printf("Correct!\n");
   exit(-1);

   return 0;
}