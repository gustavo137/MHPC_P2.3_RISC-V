#include <stdlib.h>
#include <stdio.h>

#include "rave_user_events.h"

void inner_outer(int N, int M, double *Y, double *X, double *S)
{
   rave_event_and_value(1000, 2);
   for (int i = 0; i < N;)
   {
      long gvl = __builtin_epi_vsetvl(N - i, __epi_e64, __epi_m1);
      __epi_1xf64 vec_Y = __builtin_epi_vload_1xf64(&Y[i], gvl);
      __epi_1xf64 vec_sub = __builtin_epi_vfmv_v_f_1xf64(0, gvl);
      for (int j = 0; j <= M; ++j)
      {
         __epi_1xf64 vec_X = __builtin_epi_vfmv_v_f_1xf64(X[j], gvl);
         __epi_1xf64 vec_res = __builtin_epi_vfmul_1xf64(vec_Y, vec_X, gvl);
         vec_sub = __builtin_epi_vfsub_1xf64(vec_sub, vec_res, gvl);
      }
      __epi_1xf64 vec_S = __builtin_epi_vload_1xf64(&S[i], gvl);
      vec_Y = __builtin_epi_vfmul_1xf64(vec_Y, vec_S, gvl);
      vec_Y = __builtin_epi_vfmul_1xf64(vec_Y, vec_sub, gvl);
      __builtin_epi_vstore_1xf64(&Y[i], vec_Y, gvl);
      i += gvl;
   }
   rave_event_and_value(1000, 0);
}

/// Don't touch the main function!
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
