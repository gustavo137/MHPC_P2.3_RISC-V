/* Copyright (c) 2020, Barcelona Supercomputing Center
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met: 
 * redistributions of source code must retain the above copyright notice, this 
 * list of conditions and the following disclaimer; redistributions in binary form
 * must reproduce the above copyright notice, this list of conditions and the 
 * following disclaimer in the documentation and/or other materials provided with 
 * the distribution; neither the name of the copyright holder nor the names of its 
 * contributors may be used to endorse or promote products derived from this 
 * software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <math.h>

#ifdef PAPIREAD
  #include "papi_utils.h"
#endif

#define NINSTR 32
#define NITERS 500000000
#define NFPOPS_64 NINSTR * 4
#define NFPOPS_32 NINSTR * 8
#ifndef NPROCS
#define NPROCS 1
#endif

#if defined(__arm__)
# pragma message("Detected architecture: armv7")
#elif defined(__aarch64__)
# pragma message("Detected architecture: armv8")
#elif defined(__x86_64__)
# pragma message("Detected architecture: x86_64")
#elif defined(__PPC64__)
# pragma message("Detected architecture: PPC64")
#else
# error "Unsupported architecture. Currently supported: armv7, armv8, x86_64 and PPC64"
#endif

#if defined(SVE)
#pragma message("HOLA")
static inline void code32 (void) {
  asm("mov      x3, #16;"
      "mov      x4,  #0;"
      "whilelt  p1.s, x4, x3;"
      "fmla     z0.s, p1/m,  z0.s,  z0.s;"
      "fmla     z1.s, p1/m,  z1.s,  z1.s;"
      "fmla     z2.s, p1/m,  z2.s,  z2.s;"
      "fmla     z3.s, p1/m,  z3.s,  z3.s;"
      "fmla     z4.s, p1/m,  z4.s,  z4.s;"
      "fmla     z5.s, p1/m,  z5.s,  z5.s;"
      "fmla     z6.s, p1/m,  z6.s,  z6.s;"
      "fmla     z7.s, p1/m,  z7.s,  z7.s;"
  );
}

static inline void code64 (void) {
//  asm("mov      x3,  #8;"
//      "mov      x4,  #0;"
//      "whilelt  p1.d, x4, x3;"
//      "fmla     z0.d, p1/m,  z0.d,  z0.d;"
//      "fmla     z1.d, p1/m,  z1.d,  z1.d;"
//      "fmla     z2.d, p1/m,  z2.d,  z2.d;"
//      "fmla     z3.d, p1/m,  z3.d,  z3.d;"
//      "fmla     z4.d, p1/m,  z4.d,  z4.d;"
//      "fmla     z5.d, p1/m,  z5.d,  z5.d;"
//      "fmla     z6.d, p1/m,  z6.d,  z6.d;"
//      "fmla     z7.d, p1/m,  z7.d,  z7.d;"
//  );
  asm("mov      x3,  #8;"
      "mov      x4,  #0;"
      "whilelt  p1.d, x4, x3;"
      "fmad     z0.d, p1/m,  z0.d,  z0.d;"
      "fmad     z1.d, p1/m,  z1.d,  z1.d;"
      "fmad     z2.d, p1/m,  z2.d,  z2.d;"
      "fmad     z3.d, p1/m,  z3.d,  z3.d;"
      "fmad     z4.d, p1/m,  z4.d,  z4.d;"
      "fmad     z5.d, p1/m,  z5.d,  z5.d;"
      "fmad     z6.d, p1/m,  z6.d,  z6.d;"
      "fmad     z7.d, p1/m,  z7.d,  z7.d;"
  );
}
#elif defined(__arm__)
static inline void code32 (void) {
    __asm__("VFMA.F32 Q0,Q0,Q0;"
            "VFMA.F32 Q1,Q1,Q1;"
            "VFMA.F32 Q2,Q2,Q2;"
            "VFMA.F32 Q3,Q3,Q3;"
            "VFMA.F32 Q4,Q4,Q4;"
            "VFMA.F32 Q5,Q5,Q5;"
            "VFMA.F32 Q6,Q6,Q6;"
            "VFMA.F32 Q7,Q7,Q7;"

            "VFMA.F32 Q8,Q8,Q8;"
            "VFMA.F32 Q9,Q9,Q9;"
            "VFMA.F32 Q10,Q10,Q10;"
            "VFMA.F32 Q11,Q11,Q11;"
            "VFMA.F32 Q12,Q12,Q12;"
            "VFMA.F32 Q13,Q13,Q13;"
            "VFMA.F32 Q14,Q14,Q14;"
            "VFMA.F32 Q15,Q15,Q15;"
    );
}
#elif defined(__aarch64__)
static inline void code64 (void) {
    __asm__("FMLA V0.2D,V0.2D,V0.2D;"
            "FMLA V1.2D,V1.2D,V1.2D;"
            "FMLA V2.2D,V2.2D,V2.2D;"
            "FMLA V3.2D,V3.2D,V3.2D;"
            "FMLA V4.2D,V4.2D,V4.2D;"
            "FMLA V5.2D,V5.2D,V5.2D;"
            "FMLA V6.2D,V6.2D,V6.2D;"
            "FMLA V7.2D,V7.2D,V7.2D;"
                    
            "FMLA V8.2D,V8.2D,V8.2D;"
            "FMLA V9.2D,V9.2D,V9.2D;"
            "FMLA V10.2D,V10.2D,V10.2D;"
            "FMLA V11.2D,V11.2D,V11.2D;"
            "FMLA V12.2D,V12.2D,V12.2D;"
            "FMLA V13.2D,V13.2D,V13.2D;"
            "FMLA V14.2D,V14.2D,V14.2D;"
            "FMLA V15.2D,V15.2D,V15.2D;"

        "FMLA V16.2D,V16.2D,V16.2D;"
            "FMLA V17.2D,V17.2D,V17.2D;"
            "FMLA V18.2D,V18.2D,V18.2D;"
            "FMLA V19.2D,V19.2D,V19.2D;"
            "FMLA V20.2D,V20.2D,V20.2D;"
            "FMLA V21.2D,V21.2D,V21.2D;"
            "FMLA V22.2D,V22.2D,V22.2D;"
            "FMLA V23.2D,V23.2D,V23.2D;"
                                  
            "FMLA V24.2D,V24.2D,V24.2D;"
            "FMLA V25.2D,V25.2D,V25.2D;"
            "FMLA V26.2D,V26.2D,V26.2D;"
            "FMLA V27.2D,V27.2D,V27.2D;"
            "FMLA V28.2D,V28.2D,V28.2D;"
            "FMLA V29.2D,V29.2D,V29.2D;"
            "FMLA V30.2D,V30.2D,V30.2D;"
            "FMLA V31.2D,V31.2D,V31.2D;"
    );
}
static inline void code32 (void) {
    __asm__("FMLA V0.4S,V0.4S,V0.4S;"
            "FMLA V1.4S,V1.4S,V1.4S;"
            "FMLA V2.4S,V2.4S,V2.4S;"
            "FMLA V3.4S,V3.4S,V3.4S;"
            "FMLA V4.4S,V4.4S,V4.4S;"
            "FMLA V5.4S,V5.4S,V5.4S;"
            "FMLA V6.4S,V6.4S,V6.4S;"
            "FMLA V7.4S,V7.4S,V7.4S;"

            "FMLA V8.4S,V8.4S,V8.4S;"
            "FMLA V9.4S,V9.4S,V9.4S;"
            "FMLA V10.4S,V10.4S,V10.4S;"
            "FMLA V11.4S,V11.4S,V11.4S;"
            "FMLA V12.4S,V12.4S,V12.4S;"
            "FMLA V13.4S,V13.4S,V13.4S;"
            "FMLA V14.4S,V14.4S,V14.4S;"
            "FMLA V15.4S,V15.4S,V15.4S;"

        "FMLA V16.4S,V16.4S,V16.4S;"
            "FMLA V17.4S,V17.4S,V17.4S;"
            "FMLA V18.4S,V18.4S,V18.4S;"
            "FMLA V19.4S,V19.4S,V19.4S;"
            "FMLA V20.4S,V20.4S,V20.4S;"
            "FMLA V21.4S,V21.4S,V21.4S;"
            "FMLA V22.4S,V22.4S,V22.4S;"
            "FMLA V23.4S,V23.4S,V23.4S;"
                                  
            "FMLA V24.4S,V24.4S,V24.4S;"
            "FMLA V25.4S,V25.4S,V25.4S;"
            "FMLA V26.4S,V26.4S,V26.4S;"
            "FMLA V27.4S,V27.4S,V27.4S;"
            "FMLA V28.4S,V28.4S,V28.4S;"
            "FMLA V29.4S,V29.4S,V29.4S;"
            "FMLA V30.4S,V30.4S,V30.4S;"
            "FMLA V31.4S,V31.4S,V31.4S;"
    );
}
#elif defined(__x86_64__)
/* Multiply packed double-precision floating-point */
static inline void code64 (void) {
    __asm__("VFMADD132PD %ZMM0,%ZMM0,%ZMM0;"
            "VFMADD132PD %ZMM1,%ZMM1,%ZMM1;"
            "VFMADD132PD %ZMM2,%ZMM2,%ZMM2;"
            "VFMADD132PD %ZMM3,%ZMM3,%ZMM3;"
            "VFMADD132PD %ZMM4,%ZMM4,%ZMM4;"
            "VFMADD132PD %ZMM5,%ZMM5,%ZMM5;"
            "VFMADD132PD %ZMM6,%ZMM6,%ZMM6;"
            "VFMADD132PD %ZMM7,%ZMM7,%ZMM7;"
    );
}

/* Multiply packed single-precision floating-point */
static inline void code32 (void) {
    __asm__("VFMADD132PS %ZMM0,%ZMM0,%ZMM0;"
            "VFMADD132PS %ZMM1,%ZMM1,%ZMM1;"
            "VFMADD132PS %ZMM2,%ZMM2,%ZMM2;"
            "VFMADD132PS %ZMM3,%ZMM3,%ZMM3;"
            "VFMADD132PS %ZMM4,%ZMM4,%ZMM4;"
            "VFMADD132PS %ZMM5,%ZMM5,%ZMM5;"
            "VFMADD132PS %ZMM6,%ZMM6,%ZMM6;"
            "VFMADD132PS %ZMM7,%ZMM7,%ZMM7;"
    );
}
#elif defined(__PPC64__)
static inline void code64(void) {
  __asm__("xvmaddadp 0,0,0;"
          "xvmaddadp 1,1,1;"
          "xvmaddadp 2,2,2;"
          "xvmaddadp 3,3,3;"
          "xvmaddadp 4,4,4;"
          "xvmaddadp 5,5,5;"
          "xvmaddadp 6,6,6;"
          "xvmaddadp 7,7,7;"

          "xvmaddadp 8,8,8;"
          "xvmaddadp 9,9,9;"
          "xvmaddadp 10,10,10;"
          "xvmaddadp 11,11,11;"
          "xvmaddadp 12,12,12;"
          "xvmaddadp 13,13,13;"
          "xvmaddadp 14,14,14;"
          "xvmaddadp 15,15,15;"

          "xvmaddadp 16,16,16;"
          "xvmaddadp 17,17,17;"
          "xvmaddadp 18,18,18;"
          "xvmaddadp 19,19,19;"
          "xvmaddadp 20,20,20;"
          "xvmaddadp 21,21,21;"
          "xvmaddadp 22,22,22;"
          "xvmaddadp 23,23,23;"

          "xvmaddadp 24,24,24;"
          "xvmaddadp 25,25,25;"
          "xvmaddadp 26,26,26;"
          "xvmaddadp 27,27,27;"
          "xvmaddadp 28,28,28;"
          "xvmaddadp 29,29,29;"
          "xvmaddadp 30,30,30;"
          "xvmaddadp 31,31,31;"
  );
}

static inline void code32(void) {
  __asm__("xvmaddasp 0,0,0;"
          "xvmaddasp 1,1,1;"
          "xvmaddasp 2,2,2;"
          "xvmaddasp 3,3,3;"
          "xvmaddasp 4,4,4;"
          "xvmaddasp 5,5,5;"
          "xvmaddasp 6,6,6;"
          "xvmaddasp 7,7,7;"

          "xvmaddasp 8,8,8;"
          "xvmaddasp 9,9,9;"
          "xvmaddasp 10,10,10;"
          "xvmaddasp 11,11,11;"
          "xvmaddasp 12,12,12;"
          "xvmaddasp 13,13,13;"
          "xvmaddasp 14,14,14;"
          "xvmaddasp 15,15,15;"

          "xvmaddasp 16,16,16;"
          "xvmaddasp 17,17,17;"
          "xvmaddasp 18,18,18;"
          "xvmaddasp 19,19,19;"
          "xvmaddasp 20,20,20;"
          "xvmaddasp 21,21,21;"
          "xvmaddasp 22,22,22;"
          "xvmaddasp 23,23,23;"

          "xvmaddasp 24,24,24;"
          "xvmaddasp 25,25,25;"
          "xvmaddasp 26,26,26;"
          "xvmaddasp 27,27,27;"
          "xvmaddasp 28,28,28;"
          "xvmaddasp 29,29,29;"
          "xvmaddasp 30,30,30;"
          "xvmaddasp 31,31,32;"
  );
}
#endif

double mflopsDP[NPROCS];
double mflopsSP[NPROCS];

#if defined(__aarch64__) || defined(__x86_64__) || defined(__PPC64__)
void *getCPUFreq64(void *arg) {
  unsigned int i;
  int *id = (int *) arg;
  struct timeval t0, t1;
  // DP
#ifdef PAPIREAD
  int EventSet = papi_init();
  papi_init_read(&EventSet);
#endif
  gettimeofday(&t0, NULL);
  for(i = 0; i < NITERS; ++i) {
    code64();
  }
  gettimeofday(&t1, NULL);
#ifdef PAPIREAD
  papi_print_events(&EventSet);
#endif
  long long elapsed = (t1.tv_sec*1000000+t1.tv_usec) - (t0.tv_sec*1000000+t0.tv_usec);
  //printf("Elapsed: %llu\n", elapsed);
  double mflopsLocal = (double)NFPOPS_64*(double)NITERS / (double)elapsed;
  mflopsDP[*id] = mflopsLocal;
}
#endif

void *getCPUFreq32(void *arg) {
  unsigned int i;
  int *id = (int *) arg;
  struct timeval t2, t3;
#ifdef PAPIREAD
  int EventSet = papi_init();
  papi_init_read(&EventSet);
#endif
  // SP
  gettimeofday(&t2, NULL);
  for(i = 0; i < NITERS; ++i) {
#   if defined(__aarch64__) || defined(__x86_64__) || defined(__PPC64__)
      code32();
#   elif defined(__arm__)
      // Needed since the number of Quad Neon registers is only 16
      code32();
      code32();
#   endif
  }
  gettimeofday(&t3, NULL);
#ifdef PAPIREAD
  papi_print_events(&EventSet);
#endif
  long long elapsed = (t3.tv_sec*1000000+t3.tv_usec) - (t2.tv_sec*1000000+t2.tv_usec);
  double mflopsLocal = (double)NFPOPS_32*(double)NITERS / (double)elapsed;
  mflopsSP[*id] = mflopsLocal;
}

double sum(int n, int sp) {
  unsigned int i;
  double aux = 0.0;
  for ( i = 0; i < n; i++ ) {
    if ( sp == 0 ) aux += mflopsDP[i];
    else aux += mflopsSP[i];
  }
  return aux;
}

double max(int n, int dp) {
  unsigned int i;
  double aux = 0.0;
  for (i = 0; i<n; i++ ) {
    if (dp == 1 ) {
      if (mflopsDP[i] > aux) aux = mflopsDP[i];
    } else {
      if (mflopsSP[i] > aux) aux = mflopsSP[i];
    }
  }
  return aux;
}

double min(int n, int dp) {
  unsigned int i;
  double aux;
  if (dp == 1) aux = mflopsDP[0];
  else aux = mflopsSP[0];
  for (i = 1; i<n; i++ ) {
    if (dp == 1 ) {
      if (mflopsDP[i] < aux) aux = mflopsDP[i];
    } else {
      if (mflopsSP[i] < aux) aux = mflopsSP[i];
    }
  }
  return aux;
}

double my_stddev(int n, int dp) {
  unsigned int i;
  double mean = 0.0, sum_deviation = 0.0;
  if ( dp == 1 ) {
    for (i = 0; i < n; i++) {
      mean += mflopsDP[i]/1000.0;
    }
    mean /= n;
    for ( i = 0; i < n; i++ ) {
      sum_deviation += (mflopsDP[i]/1000.0-mean)*(mflopsDP[i]/1000.0-mean);
    }
  } else {
    for ( i = 0; i<n; i++ ) {
      mean += mflopsSP[i]/1000.0;
    }
    mean /= n;
    for ( i = 0; i<n; i++ ) {
      sum_deviation += (mflopsSP[i]/1000.0-mean)*(mflopsSP[i]/1000.0-mean);
    }
  }
  return sqrt(sum_deviation/n);
}

double average(int n, double perf) {
  return perf / n;
}

int main(int argc, char **argv) {
    int n_procs;
  unsigned int i;
    struct timeval t0, t1;
  double perfSP = 0.0, perfDP = 0.0, totPerfSP = 0.0, totPerfDP = 0.0;

  n_procs = NPROCS;
  fprintf(stdout, "NPROCS: %d\n", NPROCS);

  pthread_t h[n_procs];
  int ids[n_procs];
#if defined(__aarch64__) || defined(__x86_64__) || defined(__PPC64__)
  for(i = 0; i<n_procs; ++i) {
    ids[i] = i;
    pthread_create(&h[i], NULL, getCPUFreq64, (void *) &ids[i]);
  }
  for(i = 0; i<n_procs; ++i) {
    pthread_join(h[i], NULL);
  }
  totPerfDP = sum(n_procs, 0);
  perfDP = average(n_procs, totPerfDP);
  fprintf(stdout, "SIMD DP GFlops (avg,tot,max,min,stddev) = %f, %f, %f, %f, %f\n", perfDP/1000.0, totPerfDP/1000.0, max(n_procs,1)/1000.0, min(n_procs,1)/1000.0, my_stddev(n_procs,1));
#endif

  for(i = 0; i<n_procs; ++i) {
    ids[i] = i;
    pthread_create(&h[i], NULL, getCPUFreq32, (void *) &ids[i]);
  }
  for(i = 0; i<n_procs; ++i) {
    pthread_join(h[i], NULL);
  }
  totPerfSP = sum(n_procs, 1);
  perfSP = average(n_procs, totPerfSP);
  fprintf(stdout, "SIMD SP GFlops (avg,tot,max,min,stddev) = %f, %f, %f, %f, %f\n", perfSP/1000.0, totPerfSP/1000.0, max(n_procs,0)/1000.0, min(n_procs,0)/1000.0, my_stddev(n_procs,0));

    return 0;

}

