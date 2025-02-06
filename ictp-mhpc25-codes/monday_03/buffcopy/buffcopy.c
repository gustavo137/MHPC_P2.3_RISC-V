#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/time.h>
#define t_time unsigned long int
t_time getmicros(){
			struct timeval tv;
			gettimeofday(&tv, NULL);
			return tv.tv_sec*1e6 + tv.tv_usec;
}


double BuffCopy(int N, double * A, double * B, int reps){
	
	//Cold Copy
	for(int i=0; i<N; ++i){
		B[i] = A[i];
	}
	
	//Measured Copy
	t_time ini = getmicros();
	for (int r=0; r<reps; ++r){
		int i;
		for(i=0; i<=N-8; i+=8){
			double a0 = A[i+0];
			double a1 = A[i+1];
			double a2 = A[i+2];
			double a3 = A[i+3];
			double a4 = A[i+4];
			double a5 = A[i+5];
			double a6 = A[i+6];
			double a7 = A[i+7];
			B[i+0] = a0;
			B[i+1] = a1;
			B[i+2] = a2;
			B[i+3] = a3;
			B[i+4] = a4;
			B[i+5] = a5;
			B[i+6] = a6;
			B[i+7] = a7;
		}
		for( ; i<N; ++i) B[i] = A[i];
	}
	t_time fin = getmicros();
	return (double)(fin-ini)/reps;
}

int main(int argc, char * argv[]){
	
	if (argc < 2){
		printf("Need argument: Max Bytes\n");
		exit(-1);
	}
	int Bytes = atoi(argv[1]);
	if ((Bytes % 16 != 0)){
		printf("Warning! %d is no multiple of 16\n",Bytes);
		Bytes += 16 - (Bytes % 16);
		printf("Bytes is now %d\n",Bytes);
	}

	int BuffSize = Bytes / (2*sizeof(double));

	double * Buff_A = (double *) malloc(Bytes/2);
	double * Buff_B = (double *) malloc(Bytes/2);

	double time = BuffCopy(BuffSize, Buff_A, Buff_B, 10);

	printf("User\tMachine\tUsed Data(KB)\tElements(DP)\tBandwidth(MB/s)\n");
	char hostname[32];
	gethostname(hostname, 32);
	int user = getuid();
	printf("%d\t%s\t%d\t%d\t%.4f\n",user,hostname,Bytes/1024,BuffSize,(double)Bytes/(time));

	return 0;
}



