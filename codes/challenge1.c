#include <stdlib.h>
#include <stdio.h>

#include "rave_user_events.h"
/*
// original code
void spmv_csr(int M, int N, int nnz, size_t * csrRowPtr, size_t * csrColInd, double * csrVal, double * v, double * result){
    rave_event_and_value(1000,1);
   for (int i = 0; i < M; ++i) {
      result[i] = 0;
      int rowStart = csrRowPtr[i];
      int rowEnd = csrRowPtr[i + 1];
      for (int j = rowStart; j < rowEnd; ++j) {
         int col = csrColInd[j];
         result[i] += csrVal[j] * v[col];
      }
   }
    rave_event_and_value(1000,0);
}
*/
// my modification
void spmv_csr(int M, int N, int nnz, size_t *csrRowPtr, size_t *csrColInd, double *csrVal, double *v, double *result)
{
   rave_event_and_value(1000, 1);
   for (int i = 0; i < M; ++i)
   {
      result[i] = 0;
      int rowStart = csrRowPtr[i];
      int rowEnd = csrRowPtr[i + 1];
#pragma clang loop vectorize(assume_safety)
      for (int j = rowStart; j < rowEnd; ++j)
      {
         int col = csrColInd[j];
         result[i] += csrVal[j] * v[col];
      }
   }
   rave_event_and_value(1000, 0);
}

// Don't touch the main function!
int main()
{
   rave_name_event(1000, "code_region");
   rave_name_value(1000, 0, "Other");
   rave_name_value(1000, 1, "SpMV");

   int M = 512, N = 512;
   double density = 0.5;

   double *tmpmatrix;
   double nnz = (size_t)(M * N * density);
   tmpmatrix = (double *)calloc(M * N, sizeof(double));
   int max = nnz / M;
   srand(42);
   for (int i = 0; i < nnz; ++i)
   {
      int idx = rand() % (M * N);
      while (tmpmatrix[idx] != 0)
         idx = (idx + 1) % (M * N);
      tmpmatrix[idx] = 1.0;
   }

   // Construct CSR from MTX
   size_t *csrRowPtr = (size_t *)malloc(sizeof(size_t) * (M + 1));
   size_t *csrColInd = (size_t *)malloc(sizeof(size_t) * nnz);
   double *csrVal = (double *)malloc(sizeof(double) * nnz);

   int elem = 0;
   csrRowPtr[elem] = 0;
   for (int i = 0; i < M; ++i)
   {
      for (int j = 0; j < N; ++j)
      {
         if (tmpmatrix[i * N + j] != 0.0)
         {
            csrColInd[elem] = j;
            csrVal[elem] = tmpmatrix[i * N + j];
            ++elem;
         }
      }
      csrRowPtr[i + 1] = elem;
   }
   free(tmpmatrix);

   double *v = (double *)aligned_alloc(512 / 8, sizeof(double) * (N));
   double *result = (double *)aligned_alloc(512 / 8, sizeof(double) * (M));
#pragma clang loop vectorize(disable)
   for (int i = 0; i < N; ++i)
   {
      v[i] = (double)i;
   }
#pragma clang loop vectorize(disable)
   for (int i = 0; i < M; ++i)
   {
      result[i] = 0.0;
   }

   spmv_csr(M, N, nnz, csrRowPtr, csrColInd, csrVal, v, result);

   for (int i = 0; i < M; ++i)
   {
      double res = 0;
      int rowStart = csrRowPtr[i];
      int rowEnd = csrRowPtr[i + 1];
#pragma clang loop vectorize(disable)
      for (int j = rowStart; j < rowEnd; ++j)
      {
         int col = csrColInd[j];
         res += csrVal[j] * v[col];
      }
      double diff = res - result[i];
      if (diff * diff > 1e-3)
      {
         printf("Incorrect result!");
         exit(-1);
      }
   }
   printf("Correct!\n");
   exit(-1);

   return 0;
}
