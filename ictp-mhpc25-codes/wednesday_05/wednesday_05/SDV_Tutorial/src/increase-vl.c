#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "sdv_tracing.h"

double ComputeDelta(int N, int M, double * next, double * prev){
	double global_delta = 0.0;
	trace_event_and_value(1000,4);
	for(int ij=0; ij<N*M; ++ij){
		double delta = next[ij] - prev[ij];
		global_delta += (delta*delta);
	}
	trace_event_and_value(1000,0);
	return global_delta;
}


#define BLOCK_DIM_X 160
#define BLOCK_DIM_Y 32
void Step(int N, int M, double * restrict volumes, double * restrict pressures, double * restrict temperatures, double * restrict new_temperatures, int * restrict bounds){

	trace_event_and_value(1000,1);
	for(int ij=0; ij<N*M; ++ij){
		pressures[ij] = (volumes[ij]>1.0) ? cbrt(volumes[ij]) : 0.5; 
	}
	trace_event_and_value(1000,5);
	for(int ij=0; ij<N*M; ++ij){
			pressures[ij] += (temperatures[ij]-new_temperatures[ij]);
	}
	trace_event_and_value(1000,0);

	trace_event_and_value(1000,2);
	for(long block_i=1; block_i<N-BLOCK_DIM_Y; block_i+=BLOCK_DIM_Y){
		for(long block_j=1; block_j<M-BLOCK_DIM_X; block_j+=BLOCK_DIM_X){
			for(long i=block_i; i<block_i+BLOCK_DIM_Y; ++i){
				for(long j=block_j; j<block_j+BLOCK_DIM_X; ++j){
					new_temperatures[i*M + j] = 0.25*(temperatures[M*i + j + 1]
					                                + temperatures[M*(i+1) + j]
																					+ temperatures[M*i + (j-1)]
																					+ temperatures[M*(i-1) + j]);
				}
			}
		}
	}
	trace_event_and_value(1000,0);

	trace_event_and_value(1000,3);
	for(int ij=0; ij<N*M; ++ij){
		volumes[ij] = pressures[bounds[ij]] * new_temperatures[ij];
	}
	trace_event_and_value(1000,0);
}

void initialize_2d_rand(int N, int M, double * array){
	for(int i=0; i<N; ++i){
		for(int j=0; j<M; ++j){
			array[i*M + j] = (rand()%1024) / 1024.0;
		}
	}
}
void initialize_2d_zero(int N, int M, double * array){
	for(int i=0; i<N; ++i){
		for(int j=0; j<M; ++j){
			array[i*M + j] = 0; 
		}
	}
}
void initialize_indexes(int N, int M, int * indexes){
	for(int i=0; i<N; ++i){
		for(int j=0; j<M; ++j){
			indexes[i*M + j] = (unsigned int)(((i+1) * 92401) ^ ((j+1) * 100003) ^ ((i+1)*(j+1) * 21031))%(N*M);
		}
	}
}

#include <sys/time.h>
#include <stdio.h>
 
double GetMicros(){ 
	  struct timeval tv;
	  gettimeofday(&tv, NULL);
		return (double)tv.tv_sec*1e6 + (double)tv.tv_usec;
}

int main(){

	int N=320 +2;
	int M=160 +2;

	double * volumes = (double *)malloc(sizeof(double) * N*M);
	double * temperatures = (double *)malloc(sizeof(double) * N*M);
	double * new_temperatures = (double *)malloc(sizeof(double) * N*M);
	double * pressures = (double *)malloc(sizeof(double) * N*M);
	int * bounds = (int *)malloc(sizeof(int)*N*M);

	const char * v_names[] = {"Other","Pressures_cbrt","Temperatures","Volumes","Delta","Pressures_vec"};
  int values[] = {0,1,2,3,4,5};
  trace_name_event_and_values(1000, "code_region", sizeof(values)/sizeof(values[0]), values, v_names);
	trace_init();

	srand(0);
	initialize_2d_rand(N,M,volumes);
	initialize_2d_rand(N,M,temperatures);
	initialize_2d_zero(N,M,new_temperatures);
	initialize_2d_zero(N,M,pressures);
	initialize_indexes(N,M,bounds);

	double MicrosPerStep=0.0;
	int timestep;
	for(timestep=0; timestep<10; ++timestep){
		double t1 = GetMicros();
		Step(N, M, volumes, pressures, temperatures, new_temperatures, bounds);
		double delta = ComputeDelta(N,M,new_temperatures,temperatures);
		MicrosPerStep += GetMicros() - t1;
		printf("%.4f\n",delta);
		if (delta < 1.0) break;

		double * tmp = temperatures;
		temperatures = new_temperatures;
		new_temperatures = tmp;
	}
	printf("Microseconds per step: %.2f\n", MicrosPerStep/timestep);
}
