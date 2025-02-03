#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#define t_time unsigned long int
inline t_time getmicros(){
			struct timeval tv;
			gettimeofday(&tv, NULL);
			return tv.tv_sec*1e6 + tv.tv_usec;
}

uint64_t * IniMem_ptrChase(uint64_t N_bytes, uint64_t PageSize, uint64_t CacheLine){
	uint64_t N_pages = N_bytes / PageSize;
	uint64_t * buffer = (uint64_t*)aligned_alloc(PageSize,N_bytes);

	uint64_t * base_buffer = buffer;
	uint64_t addr = 0; 
	uint64_t N_accesses = (N_bytes / CacheLine); 
	int offset = PageSize / sizeof(uint64_t);
	for(int i=0; i<N_accesses; ++i){
		uint64_t next_addr = i==N_accesses-1 ? (uint64_t)0 : (addr + offset + 8) % (N_bytes/sizeof(uint64_t));
		buffer[addr]  = (uint64_t)&base_buffer[next_addr];
		addr = next_addr;
	}
	return buffer;
}


void MemHierarchy(uint64_t MaxBytes, uint64_t PageSize, uint64_t CacheLine, int reps){

	printf("User\tMachine\tsize(KB)\tstride(bytes)\tCacheLine\tLatency(ns)\n");
	char hostname[32];
	gethostname(hostname, 32);
	int user = getuid();


	for (uint64_t Bytes = 1024; Bytes <= (MaxBytes); Bytes<<=1){
		uint64_t N_accesses = (Bytes / CacheLine) * reps;
		if(N_accesses <= 0) continue;

		uint64_t * buffer = IniMem_ptrChase(Bytes, PageSize, CacheLine);
		//Cold run
		{
			uint64_t * data;
			data = buffer;
			for(int a=0; a<N_accesses; ++a)	data = (uint64_t *)*(data);
			volatile uint64_t noopt = *data;
		}

		//Measured hot run
		{
			t_time ini = getmicros();
			uint64_t * data = buffer;
			for(int a=0; a<N_accesses; ++a)	data = (uint64_t *)*(data);
			t_time fin = getmicros();
			volatile uint64_t noopt = *data;
			double time = (double)(fin-ini)/N_accesses;
			printf("%d\t%s\t%lu\t%lu\t%lu\t%.2f\n",user,hostname,Bytes>>10,PageSize,CacheLine,time*1e3);
		}
		free(buffer);
		if (reps>1) reps >>=1;
	}
}


int main(int argc, char * argv[]){
	uint64_t MaxBytes = 1024ull*1024ull*256ull; //256MB
	int CacheLine = 64;
	int PageSize = 4096;
	int reps = 16*1024;
	for(int i=0; i<argc; ++i){
		if (strcmp(argv[i], "-B")==0){
				i++;
				if (i>=argc){
					printf("Need Number of Bytes after -B option\n");
					exit(-1);
				}
				MaxBytes = atoi(argv[i]);
		}
		if (strcmp(argv[i], "-L")==0){
				i++;
				if (i>=argc){
					printf("Need Line size in bytes after -L option\n");
					exit(-1);
				}
				CacheLine = atoi(argv[i]);
		}
		if (strcmp(argv[i], "-P")==0){
				i++;
				if (i>=argc){
					printf("Need Page size in bytes after -P option\n");
					exit(-1);
				}
				PageSize = atoi(argv[i]);
		}
		if (strcmp(argv[i], "-R")==0){
				i++;
				if (i>=argc){
					printf("Need number of max repetitions after -R option\n");
					exit(-1);
				}
				reps = atoi(argv[i]);
		}
	}
	printf("Running MemHierarchy test with up to %lu Bytes and Cacheline of %d, %d reps\n", MaxBytes,CacheLine,reps); 

	MemHierarchy(MaxBytes,PageSize,CacheLine,reps);

	return 0;
}
