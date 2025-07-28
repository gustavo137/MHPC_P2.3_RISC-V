#include <stdlib.h>
#include <stdio.h>

#include "rave_user_events.h"

void start_end(int N, double *A, double *B, double *C, double *R, int start, int end)
{
   rave_event_and_value(1000, 1);
   for (int i = 0; i < N; ++i)
   {
      C[i] = (A[i] + B[i]) / 2.0;
   }
   R[0] = C[start];
   R[1] = C[end];
   rave_event_and_value(1000, 0);
}

// Don't touch the main function!
int main()
{
   rave_name_event(1000, "code_region");
   rave_name_value(1000, 0, "Other");
   rave_name_value(1000, 1, "StartEnd");

   int N = 4096;
   int N2 = N / 2;

   double *A = (double *)malloc(sizeof(double) * N);
   double *B = (double *)malloc(sizeof(double) * N);
   double *C = (double *)malloc(sizeof(double) * N);
#pragma clang loop vectorize(disable)
   for (int i = 0; i < N; ++i)
   {
      A[i] = (double)i;
      B[i] = (double)32.0;
      C[i] = 0;
   }
   double R[2];
   int start = 13;
   int end = 3756;

   start_end(N, A, B, C, R, start, end);

   for (int i = 0; i < N; ++i)
   {
      double diff = C[i] - (B[i] + A[i]) / 2.0;
      if (i == start)
         diff += R[0] - C[i];
      if (i == end)
         diff += R[1] - C[i];
      if (diff * diff > 1e-3)
      {
         printf("Incorrect Result!\n");
         exit(-1);
      }
   }
   printf("Correct!\n");

   return 0;
}