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
#define NFPOPS NINSTR * 2
#ifndef NPROCS
#define NPROCS 1
#endif

#if defined(__arm__)
# pragma message("Detected architecture: ARMv7")
#elif defined(__aarch64__)
# pragma message("Detected architecture: ARMv8")
#elif defined(__x86_64__)
# pragma message("Detected architecture: x86_64")
#elif defined(__PPC64__)
# pragma message("Detected architecture: PPC64")
#else
# error "Unsupported architecture. Currently supported: armv7, armv8, x86_64 and PPC64"
#endif

#if defined(__arm__)
static inline void code64 (void) {
    __asm__("VFMA.F64 D0,D0,D0;"
            "VFMA.F64 D1,D1,D1;"
            "VFMA.F64 D2,D2,D2;"
            "VFMA.F64 D3,D3,D3;"
            "VFMA.F64 D4,D4,D4;"
            "VFMA.F64 D5,D5,D5;"
            "VFMA.F64 D6,D6,D6;"
            "VFMA.F64 D7,D7,D7;"

            "VFMA.F64 D8,D8,D8;"
            "VFMA.F64 D9,D9,D9;"
            "VFMA.F64 D10,D10,D10;"
            "VFMA.F64 D11,D11,D11;"
            "VFMA.F64 D12,D12,D12;"
            "VFMA.F64 D13,D13,D13;"
            "VFMA.F64 D14,D14,D14;"
            "VFMA.F64 D15,D15,D15;"

            "VFMA.F64 D16,D16,D16;"
            "VFMA.F64 D17,D17,D17;"
            "VFMA.F64 D18,D18,D18;"
            "VFMA.F64 D19,D19,D19;"
            "VFMA.F64 D20,D20,D20;"
            "VFMA.F64 D21,D21,D21;"
            "VFMA.F64 D22,D22,D22;"
            "VFMA.F64 D23,D23,D23;"

            "VFMA.F64 D24,D24,D24;"
            "VFMA.F64 D25,D25,D25;"
            "VFMA.F64 D26,D26,D26;"
            "VFMA.F64 D27,D27,D27;"
            "VFMA.F64 D28,D28,D28;"
            "VFMA.F64 D29,D29,D29;"
            "VFMA.F64 D30,D30,D30;"
            "VFMA.F64 D31,D31,D31;"
    );
}
static inline void code32 (void) {
    __asm__("VFMA.F32 S0,S0,S0;"
            "VFMA.F32 S1,S1,S1;"
            "VFMA.F32 S2,S2,S2;"
            "VFMA.F32 S3,S3,S3;"
            "VFMA.F32 S4,S4,S4;"
            "VFMA.F32 S5,S5,S5;"
            "VFMA.F32 S6,S6,S6;"
            "VFMA.F32 S7,S7,S7;"

            "VFMA.F32 S8,S8,S8;"
            "VFMA.F32 S9,S9,S9;"
            "VFMA.F32 S10,S10,S10;"
            "VFMA.F32 S11,S11,S11;"
            "VFMA.F32 S12,S12,S12;"
            "VFMA.F32 S13,S13,S13;"
            "VFMA.F32 S14,S14,S14;"
            "VFMA.F32 S15,S15,S15;"

            "VFMA.F32 S16,S16,S16;"
            "VFMA.F32 S17,S17,S17;"
            "VFMA.F32 S18,S18,S18;"
            "VFMA.F32 S19,S19,S19;"
            "VFMA.F32 S20,S20,S20;"
            "VFMA.F32 S21,S21,S21;"
            "VFMA.F32 S22,S22,S22;"
            "VFMA.F32 S23,S23,S23;"

            "VFMA.F32 S24,S24,S24;"
            "VFMA.F32 S25,S25,S25;"
            "VFMA.F32 S26,S26,S26;"
            "VFMA.F32 S27,S27,S27;"
            "VFMA.F32 S28,S28,S28;"
            "VFMA.F32 S29,S29,S29;"
            "VFMA.F32 S30,S30,S30;"
            "VFMA.F32 S31,S31,S31;"
    );
}
#elif defined(__aarch64__)
static inline void code64 (void) {
    __asm__("FMADD D0,D0,D0,D0;"
            "FMADD D1,D1,D1,D1;"
            "FMADD D2,D2,D2,D2;"
            "FMADD D3,D3,D3,D3;"
            "FMADD D4,D4,D4,D4;"
            "FMADD D5,D5,D5,D5;"
            "FMADD D6,D6,D6,D6;"
            "FMADD D7,D7,D7,D7;"
                              
            "FMADD D8,D8,D8,D8;"
            "FMADD D9,D9,D9,D9;"
            "FMADD D10,D10,D10,D10;"
            "FMADD D11,D11,D11,D11;"
            "FMADD D12,D12,D12,D12;"
            "FMADD D13,D13,D13,D13;"
            "FMADD D14,D14,D14,D14;"
            "FMADD D15,D15,D15,D15;"
                                  
            "FMADD D16,D16,D16,D16;"
            "FMADD D17,D17,D17,D17;"
            "FMADD D18,D18,D18,D18;"
            "FMADD D19,D19,D19,D19;"
            "FMADD D20,D20,D20,D20;"
            "FMADD D21,D21,D21,D21;"
            "FMADD D22,D22,D22,D22;"
            "FMADD D23,D23,D23,D23;"
                                  
            "FMADD D24,D24,D24,D24;"
            "FMADD D25,D25,D25,D25;"
            "FMADD D26,D26,D26,D26;"
            "FMADD D27,D27,D27,D27;"
            "FMADD D28,D28,D28,D28;"
            "FMADD D29,D29,D29,D29;"
            "FMADD D30,D30,D30,D30;"
            "FMADD D31,D31,D31,D31;"
    );
}
static inline void code32 (void) {
    __asm__("FMADD S0,S0,S0,S0;"
            "FMADD S1,S1,S1,S1;"
            "FMADD S2,S2,S2,S2;"
            "FMADD S3,S3,S3,S3;"
            "FMADD S4,S4,S4,S4;"
            "FMADD S5,S5,S5,S5;"
            "FMADD S6,S6,S6,S6;"
            "FMADD S7,S7,S7,S7;"

            "FMADD S8,S8,S8,S8;"
            "FMADD S9,S9,S9,S9;"
            "FMADD S10,S10,S10,S10;"
            "FMADD S11,S11,S11,S11;"
            "FMADD S12,S12,S12,S12;"
            "FMADD S13,S13,S13,S13;"
            "FMADD S14,S14,S14,S14;"
            "FMADD S15,S15,S15,S15;"

            "FMADD S16,S16,S16,S16;"
            "FMADD S17,S17,S17,S17;"
            "FMADD S18,S18,S18,S18;"
            "FMADD S19,S19,S19,S19;"
            "FMADD S20,S20,S20,S20;"
            "FMADD S21,S21,S21,S21;"
            "FMADD S22,S22,S22,S22;"
            "FMADD S23,S23,S23,S23;"

            "FMADD S24,S24,S24,S24;"
            "FMADD S25,S25,S25,S25;"
            "FMADD S26,S26,S26,S26;"
            "FMADD S27,S27,S27,S27;"
            "FMADD S28,S28,S28,S28;"
            "FMADD S29,S29,S29,S29;"
            "FMADD S30,S30,S30,S30;"
            "FMADD S31,S31,S31,S31;"
    );
}
#elif defined(__x86_64__)
static inline void code64 (void) {
    __asm__("VFMADD132SD %XMM0,%XMM0,%XMM0;"
            "VFMADD132SD %XMM1,%XMM1,%XMM1;"
            "VFMADD132SD %XMM2,%XMM2,%XMM2;"
            "VFMADD132SD %XMM3,%XMM3,%XMM3;"
            "VFMADD132SD %XMM4,%XMM4,%XMM4;"
            "VFMADD132SD %XMM5,%XMM5,%XMM5;"
            "VFMADD132SD %XMM6,%XMM6,%XMM6;"
            "VFMADD132SD %XMM7,%XMM7,%XMM7;"

            "VFMADD132SD %XMM8,%XMM8,%XMM8;"
            "VFMADD132SD %XMM9,%XMM9,%XMM9;"
            "VFMADD132SD %XMM10,%XMM10,%XMM10;"
            "VFMADD132SD %XMM11,%XMM11,%XMM11;"
            "VFMADD132SD %XMM12,%XMM12,%XMM12;"
            "VFMADD132SD %XMM13,%XMM13,%XMM13;"
            "VFMADD132SD %XMM14,%XMM14,%XMM14;"
            "VFMADD132SD %XMM15,%XMM15,%XMM15;"

            "VFMADD132SD %XMM16,%XMM16,%XMM16;"
            "VFMADD132SD %XMM17,%XMM17,%XMM17;"
            "VFMADD132SD %XMM18,%XMM18,%XMM18;"
            "VFMADD132SD %XMM19,%XMM19,%XMM19;"
            "VFMADD132SD %XMM20,%XMM20,%XMM20;"
            "VFMADD132SD %XMM21,%XMM21,%XMM21;"
            "VFMADD132SD %XMM22,%XMM22,%XMM22;"
            "VFMADD132SD %XMM23,%XMM23,%XMM23;"

            "VFMADD132SD %XMM24,%XMM24,%XMM24;"
            "VFMADD132SD %XMM25,%XMM25,%XMM25;"
            "VFMADD132SD %XMM26,%XMM26,%XMM26;"
            "VFMADD132SD %XMM27,%XMM27,%XMM27;"
            "VFMADD132SD %XMM28,%XMM28,%XMM28;"
            "VFMADD132SD %XMM29,%XMM29,%XMM29;"
            "VFMADD132SD %XMM30,%XMM30,%XMM30;"
            "VFMADD132SD %XMM31,%XMM31,%XMM31;"
    );
}

static inline void code32 (void) {
    __asm__("VFMADD132SS %XMM0,%XMM0,%XMM0;"
            "VFMADD132SS %XMM1,%XMM1,%XMM1;"
            "VFMADD132SS %XMM2,%XMM2,%XMM2;"
            "VFMADD132SS %XMM3,%XMM3,%XMM3;"
            "VFMADD132SS %XMM4,%XMM4,%XMM4;"
            "VFMADD132SS %XMM5,%XMM5,%XMM5;"
            "VFMADD132SS %XMM6,%XMM6,%XMM6;"
            "VFMADD132SS %XMM7,%XMM7,%XMM7;"

            "VFMADD132SS %XMM8,%XMM8,%XMM8;"
            "VFMADD132SS %XMM9,%XMM9,%XMM9;"
            "VFMADD132SS %XMM10,%XMM10,%XMM10;"
            "VFMADD132SS %XMM11,%XMM11,%XMM11;"
            "VFMADD132SS %XMM12,%XMM12,%XMM12;"
            "VFMADD132SS %XMM13,%XMM13,%XMM13;"
            "VFMADD132SS %XMM14,%XMM14,%XMM14;"
            "VFMADD132SS %XMM15,%XMM15,%XMM15;"

            "VFMADD132SS %XMM16,%XMM16,%XMM16;"
            "VFMADD132SS %XMM17,%XMM17,%XMM17;"
            "VFMADD132SS %XMM18,%XMM18,%XMM18;"
            "VFMADD132SS %XMM19,%XMM19,%XMM19;"
            "VFMADD132SS %XMM20,%XMM20,%XMM20;"
            "VFMADD132SS %XMM21,%XMM21,%XMM21;"
            "VFMADD132SS %XMM22,%XMM22,%XMM22;"
            "VFMADD132SS %XMM23,%XMM23,%XMM23;"

            "VFMADD132SS %XMM24,%XMM24,%XMM24;"
            "VFMADD132SS %XMM25,%XMM25,%XMM25;"
            "VFMADD132SS %XMM26,%XMM26,%XMM26;"
            "VFMADD132SS %XMM27,%XMM27,%XMM27;"
            "VFMADD132SS %XMM28,%XMM28,%XMM28;"
            "VFMADD132SS %XMM29,%XMM29,%XMM29;"
            "VFMADD132SS %XMM30,%XMM30,%XMM30;"
            "VFMADD132SS %XMM31,%XMM31,%XMM31;"
    );
}
#elif defined(__PPC64__)
static inline void code64 (void) {
    __asm__("fmul 0,0,0;"
            "fmul 1,1,1;"
            "fmul 2,2,2;"
            "fmul 3,3,3;"
            "fmul 4,4,4;"
            "fmul 5,5,5;"
            "fmul 6,6,6;"
            "fmul 7,7,7;"

            "fmul 8,8,8;"
            "fmul 9,9,9;"
            "fmul 10,10,10;"
            "fmul 11,11,11;"
            "fmul 12,12,12;"
            "fmul 13,13,13;"
            "fmul 14,14,14;"
            "fmul 15,15,15;"

            "fmul 16,16,16;"
            "fmul 17,17,17;"
            "fmul 18,18,18;"
            "fmul 19,19,19;"
            "fmul 20,20,20;"
            "fmul 21,21,21;"
            "fmul 22,22,22;"
            "fmul 23,23,23;"

            "fmul 24,24,24;"
            "fmul 25,25,25;"
            "fmul 26,26,26;"
            "fmul 27,27,27;"
            "fmul 28,28,28;"
            "fmul 29,29,29;"
            "fmul 30,30,30;"
            "fmul 31,31,31;"
    );
}

static inline void code32 (void) {
    __asm__("fmuls 0,0,0;"
            "fmuls 1,1,1;"
            "fmuls 2,2,2;"
            "fmuls 3,3,3;"
            "fmuls 4,4,4;"
            "fmuls 5,5,5;"
            "fmuls 6,6,6;"
            "fmuls 7,7,7;"

            "fmuls 8,8,8;"
            "fmuls 9,9,9;"
            "fmuls 10,10,10;"
            "fmuls 11,11,11;"
            "fmuls 12,12,12;"
            "fmuls 13,13,13;"
            "fmuls 14,14,14;"
            "fmuls 15,15,15;"

            "fmuls 16,16,16;"
            "fmuls 17,17,17;"
            "fmuls 18,18,18;"
            "fmuls 19,19,19;"
            "fmuls 20,20,20;"
            "fmuls 21,21,21;"
            "fmuls 22,22,22;"
            "fmuls 23,23,23;"

            "fmuls 24,24,24;"
            "fmuls 25,25,25;"
            "fmuls 26,26,26;"
            "fmuls 27,27,27;"
            "fmuls 28,28,28;"
            "fmuls 29,29,29;"
            "fmuls 30,30,30;"
            "fmuls 31,31,31;"
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
	double mflopsLocal = (double)NFPOPS*(double)NITERS / (double)elapsed;
	mflopsDP[*id] = mflopsLocal;
}
#endif

void *getCPUFreq32(void *arg) {
	unsigned int i;
	int *id = (int *) arg;
	struct timeval t2, t3;
	// SP
#ifdef PAPIREAD
	int EventSet = papi_init();
    papi_init_read(&EventSet);
#endif
	gettimeofday(&t2, NULL);
	for(i = 0; i < NITERS; ++i) {
	  code32();
	}
	gettimeofday(&t3, NULL);
#ifdef PAPIREAD
        papi_print_events(&EventSet);
#endif
	long long elapsed = (t3.tv_sec*1000000+t3.tv_usec) - (t2.tv_sec*1000000+t2.tv_usec);
	double mflopsLocal = (double)NFPOPS*(double)NITERS / (double)elapsed;
	mflopsSP[*id] = mflopsLocal;
}

double sum(int n, int sp) {
	unsigned int i;
	double aux = 0.0;
	for ( i = 0; i < n; i++ ) {
		if (sp == 0) aux += mflopsDP[i];
		else aux += mflopsSP[i];
	}
	return aux;
}

double max(int n, int dp) {
	unsigned int i;
	double aux = 0.0;
	for ( i = 0; i < n; i++ ) {
		if (dp == 1) {
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
	for ( i = 1; i < n; i++ ) {
		if (dp == 1) {
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
	if (dp == 1) {
		for ( i = 0; i < n; i++) {
			mean += mflopsDP[i]/1000.0;
		}
		mean /= n;
		for ( i = 0; i < n; i++) {
			sum_deviation += (mflopsDP[i]/1000.0-mean)*(mflopsDP[i]/1000.0-mean);
		}
	} else {
		for ( i = 0; i < n; i++) {
			mean += mflopsSP[i]/1000.0;
		}
		mean /= n;
		for ( i = 0; i < n; i++) {
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
	for(i = 0; i<n_procs; ++i) {
		ids[i] = i;
		pthread_create(&h[i], NULL, getCPUFreq64, (void *) &ids[i]);
	}
	for(i = 0; i<n_procs; ++i) {
		pthread_join(h[i], NULL);
	}
	totPerfDP = sum(n_procs, 0);
	perfDP = average(n_procs, totPerfDP);
	fprintf(stdout, "FPU DP GFlops (avg,tot,max,min,stddev) = %f, %f, %f, %f, %f\n", perfDP/1000.0, totPerfDP/1000.0, max(n_procs,1)/1000.0, min(n_procs,1)/1000.0, my_stddev(n_procs,1) );

	for(i = 0; i<n_procs; ++i) {
		ids[i] = i;
		pthread_create(&h[i], NULL, getCPUFreq32, (void *) &ids[i]);
	}
	for(i = 0; i<n_procs; ++i) {
		pthread_join(h[i], NULL);
	}
	totPerfSP = sum(n_procs, 1);
	perfSP = average(n_procs, totPerfSP);
	fprintf(stdout, "FPU SP GFlops (avg,tot,max,min,stddev) = %f, %f, %f, %f, %f\n", perfSP/1000.0, totPerfSP/1000.0, max(n_procs,0)/1000.0, min(n_procs,0)/1000.0, my_stddev(n_procs,0));
    return 0;
}
