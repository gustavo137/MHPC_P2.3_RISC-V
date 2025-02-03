#include "work.h"
#include "stats.h"

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <omp.h>

#include <unistd.h>
#include <string.h>

#include <papi.h>

/***************************************************************************************************************/
/* USAGE                                                                                                       */
/***************************************************************************************************************/
void usage(int argc, char* argv[]) {
  fprintf(stdout, "Usage: %s [<options>]\n", argv[0]);
  fprintf(stdout, "  --ntimes, -n <N> Loop <N> times\n");
  fprintf(stdout, "                     Default: 100\n");
  fprintf(stdout, "  --always, -a     Loop for ever\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "  --report, -r <N> Report measurements each <N> iterations\n");
  fprintf(stdout, "                     If <N> < 0, then report once at the very end\n");
  fprintf(stdout, "                     Default: -1\n");
  fprintf(stdout, "  --detail, -d     Report measurements for each thread\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "  --quiet,  -q     Do not print any output\n");
  fprintf(stdout, "  --noheader       Omit CSV header from output\n");
  fprintf(stdout, "\n");
  fprintf(stdout, "  --help,   -h     Print this message\n");
  fprintf(stdout, "\n\n");
  fprintf(stdout, "Recommended environment variables\n");
  fprintf(stdout, "  OMP_NUM_THREADS\n");
  fprintf(stdout, "  OMP_PLACES (eg. cores)\n");
  fprintf(stdout, "  OMP_PROC_BIND (eg. close, spead)\n");
  fprintf(stdout, "\n\n");
  fprintf(stdout, "Reporting\n");
  fprintf(stdout, "  Time (us) measured with gettimeofday\n");
  fprintf(stdout, "  Cycles measured with PAPI_TOT_CYC\n");
  fprintf(stdout, "  Floating Point operations known at compile time\n");
  fprintf(stdout, "    NFPOPS = %llu\n", NFPOPS);
  fprintf(stdout, "    NITERS = %d\n", NITERS);
  fprintf(stdout, "    Total FP operations: NFPOPS*NITERS = %llu\n", NFPOPS*NITERS);
  exit(EXIT_SUCCESS);
}

/***************************************************************************************************************/
/* TRACING                                                                                                     */
/***************************************************************************************************************/
unsigned long get_thread_num() { return omp_get_thread_num(); }

int init_tracing() {
  int retval;

  retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT) {
    fprintf(stderr,"Error initializing PAPI! %s\n", PAPI_strerror(retval));
    return -1;
  }

  retval = PAPI_thread_init(get_thread_num);
  if (retval != PAPI_OK) {
    fprintf(stderr,"Error initializing threads in PAPI! %s\n", PAPI_strerror(retval));
    return -1;
  }

  return 0;
}



/***************************************************************************************************************/
/* MAIN                                                                                                        */
/***************************************************************************************************************/
int main(int argc, char* argv[]) {
  int i;
  int retval;
  int num_threads;

  long ntimes = 100;

  long report = -1;

  int detail = 0;
  int always = 0;
  int quiet  = 0;
  int noheader = 0;

  long long* cycles_global;
  long long* instructions_global;
  long long* us_global;
  double* ghz_global;
  double* flopc_global;
  double* gflops_global;
  double* ipc_global;

  double gflops_tot;
  double gflops_avg;
  double gflops_max;
  double gflops_min;
  double gflops_std;
  double std_over_avg;
  double avg_over_max;

  retval = init_tracing();
  if (retval != 0) { return retval; }

  for (i = 1; i < argc; i++) {
    if      (strcmp("--ntimes", argv[i]) == 0 || strcmp("-n", argv[i]) == 0) {
      if (i+1 >= argc) {
        fprintf(stderr, "Incorrect number of parameters\n");
        usage(argc, argv);
      }

      ntimes = atol(argv[i+1]);
      i++;
    }
    else if (strcmp("--always", argv[i]) == 0 || strcmp("-a", argv[i]) == 0) {
      always = 1;
    }

    else if (strcmp("--report", argv[i]) == 0 || strcmp("-r", argv[i]) == 0) {
      if (i+1 >= argc) {
        fprintf(stderr, "Incorrect number of parameters\n");
        usage(argc, argv);
      }

      report = atol(argv[i+1]);
      i++;
    }

    else if (strcmp("--detail", argv[i]) == 0 || strcmp("-d", argv[i]) == 0) {
      detail = 1;
    }

    else if (strcmp("--quiet",  argv[i]) == 0 || strcmp("-q", argv[i]) == 0) {
      quiet  = 1;
    }

    else if (strcmp("--help",   argv[i]) == 0 || strcmp("-h", argv[i]) == 0) {
      usage(argc, argv);
    }

    else if (strcmp("--noheader",   argv[i]) == 0) {
      noheader = 1;
    }

    else {
      fprintf(stderr, "Unrecognized option: %s\n\n", argv[i]);
      usage(argc, argv);
    }
  }

  if (report < 0) report = ntimes;

  #pragma omp parallel
  {
    int id = omp_get_thread_num();
    unsigned long i;
    struct timeval t0, t1;

    int eventset = PAPI_NULL;
    int retval_local;
    long long cycles_start, cycles_end;
    long long counters_local[2];
    long long cycles_local;
    long long instructions_local;

    long it = 0;
    long report_thread = 0;

    #pragma omp single
    {
      num_threads = omp_get_num_threads();

      /*********************************************/
      // Print Header
      /*********************************************/
      if (!noheader && !quiet) {
        if (!detail) {
          fprintf(stdout, "num_threads, iteration, gflops_tot, gflops_avg, gflops_max, gflops_min, gflops_std, std_over_avg, avg_over_max\n");
        } else {
          fprintf(stdout, "thread_id, iteration, cycles, instructions, us, fops, GHz, Flop/cycle, GFlop/s, IPC\n");
        }
      }
    
      cycles_global       = (long long*) malloc(num_threads * sizeof(long long));
      instructions_global = (long long*) malloc(num_threads * sizeof(long long));
      us_global           = (long long*) malloc(num_threads * sizeof(long long));
      ghz_global          = (double*   ) malloc(num_threads * sizeof(double   ));
      flopc_global        = (double*   ) malloc(num_threads * sizeof(double   ));
      gflops_global       = (double*   ) malloc(num_threads * sizeof(double   ));
      ipc_global          = (double*   ) malloc(num_threads * sizeof(double   ));
    }

    retval_local = PAPI_create_eventset(&eventset);
    if (retval_local != PAPI_OK) {
      fprintf(stderr,"%2d: Error creating eventset! %s\n", id, PAPI_strerror(retval_local));
    }

    retval_local = PAPI_add_named_event(eventset, "PAPI_TOT_CYC");
    if (retval_local != PAPI_OK) {
     fprintf(stderr,"%2d: Error adding %s: %s\n", id, "PAPI_TOT_CYC", PAPI_strerror(retval_local));
    }

    retval_local = PAPI_add_named_event(eventset, "PAPI_TOT_INS");
    if (retval_local != PAPI_OK) {
     fprintf(stderr,"%2d: Error adding %s: %s\n", id, "PAPI_TOT_INS", PAPI_strerror(retval_local));
    }

    cycles_global[id]       = 0;
    instructions_global[id] = 0;
    us_global[id]           = 0;

    do {
      gettimeofday(&t0, NULL);
      PAPI_start(eventset);
      for (i = 0; i < NITERS; ++i) {
        work();
      }
      PAPI_stop(eventset, counters_local);
      gettimeofday(&t1, NULL);

      cycles_local = counters_local[0];
      instructions_local = counters_local[1];

      cycles_global[id]       += cycles_local;
      instructions_global[id] += instructions_local;
      us_global[id]           += (t1.tv_sec*1000000+t1.tv_usec) - (t0.tv_sec*1000000+t0.tv_usec);

      it++;


      /*********************************************/
      // Print Summary
      /*********************************************/
      if (!quiet && (it%report) == 0) {
        ghz_global[id]    = ((double)cycles_global[id] / (double)us_global[id]) / 1000.0;
        flopc_global[id]  = (double)NFPOPS * (double)NITERS * (double)report / (double)cycles_global[id];
        gflops_global[id] = (double)NFPOPS * (double)NITERS * (double)report / (double)us_global[id] / 1000.0;
        ipc_global[id]    = (double)instructions_global[id] / (double)cycles_global[id];

        #pragma omp barrier
        if (!detail) {
          if (id == 0) {
            gflops_tot = sum(gflops_global, num_threads);
            gflops_avg = gflops_tot / (double)num_threads;
            gflops_max = max(gflops_global, num_threads);
            gflops_min = min(gflops_global, num_threads);
            gflops_std = num_threads > 1 ? std(gflops_global, num_threads) : 0.0;
            std_over_avg = gflops_std / gflops_avg;
            avg_over_max = gflops_min / gflops_avg;
          
            fprintf(stdout, "%2d,  %ld, ",  num_threads, it);
            fprintf(stdout, "%.2f, %.2f, ", gflops_tot,  gflops_avg);
            fprintf(stdout, "%.2f, %.2f, ", gflops_max,  gflops_min);
            fprintf(stdout, "%.2f, %.2f, ", gflops_std,  std_over_avg);
            fprintf(stdout, "%.2f\n", avg_over_max);
          }
        }

        else if (report_thread == id) {
          fprintf(stdout, "%2d, %ld, ",    id,                it);
          fprintf(stdout, "%llu, %llu, ",  cycles_global[id], instructions_global[id]);
          fprintf(stdout, "%llu, %llu, ",  us_global[id],     NFPOPS*NITERS);
          fprintf(stdout, "%.2f, %.2f, ",  ghz_global[id],    flopc_global[id]);
          fprintf(stdout, "%.2f, %.2f\n",  gflops_global[id], ipc_global[id]);
        }


        cycles_global[id]       = 0;
        instructions_global[id] = 0;
        us_global[id]           = 0;

        report_thread = (report_thread+1)%num_threads;
      }
    } while (always || (it < ntimes));
  }

  return 0;
}
