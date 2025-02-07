#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sdv_tracing.h>

// #define FP_t double
#define FP_t float

#include <sys/time.h>
#define t_time unsigned long int
inline t_time getmicros()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1e6 + tv.tv_usec;
}
// original
///*
inline FP_t dot(FP_t *a, FP_t *b, size_t N)
{
	FP_t sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += a[i] * b[i];
	}
	return sum;
}
//*/
/*
inline FP_t dot(FP_t * a, FP_t * b, size_t N){
		  FP_t sum = 0;
	FP_t *a_ptr = &a[0];//<<<
	FP_t *b_ptr = &b[0];//<<<
		  for(int i=0; i<N; i++){
					 //sum += a[i]*b[i];
		sum += a_ptr[i] * b_ptr[i];//<<<
		  }
		  return sum;
}
*/

inline void scale(FP_t *x, FP_t alpha, int N)
{
	for (int i = 0; i < N; i++)
	{
		x[i] *= alpha;
	}
}

inline void axpy(FP_t *x, FP_t *y, FP_t alpha, int N)
{
	for (int i = 0; i < N; i++)
	{
		y[i] += alpha * x[i];
	}
}
//<<<< new function 1
inline void scaled_axpy(FP_t *pk, FP_t *rk, FP_t beta, int N)
{
	for (int i = 0; i < N; i++)
	{
		pk[i] = beta * pk[i] + rk[i]; // Combine scale and axpy in a single operation
	}
}

//<<<<< end new function 1
inline void gemv_kernel(int M, int N, FP_t *a, FP_t *x, FP_t *y)
{
	for (size_t i = 0; i < M; i++)
	{
		y[i] = 0;
		for (size_t j = 0; j < N; j++)
		{
			y[i] += a[i * N + j] * x[j];
		}
	}
}

int cg_dense(int M, FP_t *a, FP_t *b, FP_t *x, FP_t tolerance, int itermax, int quiet)
{
	// gemv      dot     axpy   axpy    dot     scale    axpy
	FP_t flops = (2 * M * M) + (2 * M) + (2 * M) + (2 * M) + (2 * M) + (2 * M) + (2 * M);

	// 1. Allocation
	FP_t *r_k = (FP_t *)malloc(sizeof(FP_t) * M);
	FP_t *p_k = (FP_t *)malloc(sizeof(FP_t) * M);
	FP_t *Ap_k = (FP_t *)malloc(sizeof(FP_t) * M);
	FP_t *x_k = x;

	// 2. Initialization
	for (int i = 0; i < M; ++i)
	{
		x_k[i] = 0;
		r_k[i] = b[i];
		p_k[i] = b[i]; /*r_k[i]*/
		;
	}

	// 3. Iterations
	t_time total = 0;
	t_time ini, fin;

	ini = getmicros();
	// 3.0. Dot
	FP_t alpha, beta;
	FP_t rs = dot(r_k, r_k, M);
	FP_t rs_next;
	int nbiter;
	for (nbiter = 0; nbiter < itermax; ++nbiter)
	{

		trace_event_and_value(1000, 1);
		// 3.1. GEMV (Ap_k = A * p_k)
		gemv_kernel(M, M, a, p_k, Ap_k);
		trace_event_and_value(1000, 0);

		trace_event_and_value(1000, 2);
		// 3.2. Alpha = sum(p_k[i]*Ap_k[i])
		alpha = dot(p_k, Ap_k, M);
		alpha = rs / alpha;
		trace_event_and_value(1000, 0);

		trace_event_and_value(1000, 3);
		// 3.3. Axpy (x_k += alpha*p_k)
		axpy(p_k, x_k, alpha, M);

		// 3.4. Axpy (r_k -= alpha*Ap_k)
		axpy(Ap_k, r_k, -alpha, M);
		trace_event_and_value(1000, 0);

		trace_event_and_value(1000, 4);
		// 3.5. rs_next = sum(r_k[i]*r_k[i])
		rs_next = dot(r_k, r_k, M);
		trace_event_and_value(1000, 0);

		fin = getmicros();
		total += fin - ini;
		if (!quiet)
		{
			printf("iter:\t"
					 "%d\t"
					 "res:\t"
					 "%.16f\t"
					 "time:\t"
					 "%lu\n",
					 nbiter, rs_next, fin - ini);
		}
		if (rs_next < (tolerance * tolerance))
			break;
		ini = getmicros();

		trace_event_and_value(1000, 5);
		beta = rs_next / rs;
		// 3.6. Scal (p_k *= beta)
		scale(p_k, beta, M);
		trace_event_and_value(1000, 0);

		trace_event_and_value(1000, 6);
		// 3.7. Axpy (p_k += r_k);
		axpy(r_k, p_k, 1.0, M);
		trace_event_and_value(1000, 0);

		//<<<<<<
		// instead of use
		// scale(p_k, beta, M);
		// axpy(r_k, p_k, 1.0, M);
		// we use
		scaled_axpy(p_k, r_k, beta, M);
		//<<<<<,

		rs = rs_next;
	}

	// 4. Freeing
	free(r_k);
	free(p_k);
	free(Ap_k);

	flops = flops * (nbiter + 1) - 2.0 * M - 2.0 * M;
	printf("CG\t"
			 "iters\t"
			 "%d\t"
			 "Time:\t"
			 "%lu\t"
			 "Residual:\t"
			 "%.4e\n",
			 nbiter + 1, total, rs_next);

	return ++nbiter;
}

void validate_cg_dense(int M, FP_t *a, FP_t *b, FP_t *x, FP_t tolerance)
{
	// Performs a GEMV and checks against result array B
	FP_t res = 0.0;
	FP_t b_norm = 0.0;
	for (size_t i = 0; i < M; i++)
	{
		FP_t result = 0;
		for (size_t j = 0; j < M; j++)
		{
			result += a[i * M + j] * x[j];
		}
		FP_t diff = b[i] - result;
		res += diff * diff;
		b_norm += b[i] * b[i];
	}

	FP_t error = res / b_norm;
	if (error * error >= tolerance)
	{
		printf("ERROR IN VALIDATION, %.16f\n", error);
		exit(-1);
	}
}

int main(int argc, char *argv[])
{

	const char *v_names[] = {"Other", "GEMV", "Dot1", "Axpys", "Dot2", "Scale", "Final_Axpy"};
	int values[] = {0, 1, 2, 3, 4, 5, 6};
	trace_name_event_and_values(1000, "code_region", sizeof(values) / sizeof(values[0]), values, v_names);
	trace_init();

	int M = 512;
	int quiet = 0;
	FP_t tolerance = 0.0005;

	// Read arguments
	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "-m") == 0)
		{
			++i;
			M = atoi(argv[i]);
		}
		else if (strcmp(argv[i], "-t") == 0)
		{
			++i;
			tolerance = atof(argv[i]);
		}
		else if (strcmp(argv[i], "-q") == 0)
		{
			quiet = 1;
		}
		else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
		{
			printf("Use the argument <-m M> to pass the matrix's size\n");
			printf("Use the argument <-t T> to pass the tolerance (e.g. 0.0001)\n");
			printf("Use the argument <-q> to remove all iteration's prints\n");
			exit(-1);
		}
	}
	int itermax = M * 5;
	printf("Running with a [%d]x[%d] Matrix and tolerance of %.1e\n", M, M, tolerance);

	// Initialize data
	FP_t *a = (FP_t *)malloc(sizeof(FP_t) * M * M);
	for (int i = 0; i < M; ++i)
	{
		FP_t sum = 0;
		for (int j = i + 1; j < M; ++j)
		{
			FP_t value = (rand() % 1024) / 1024.0;
			a[i * M + j] = value;
			a[j * M + i] = value; // Symmetry
			sum += value;
		}
		// Make diagonals larger than the sum of the row
		a[i * M + i] = 2 * sum + 2.0;
	}

	for (int i = 0; i < M; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			if (a[i * M + j] != a[j * M + i])
				printf("error\n");
		}
	}
	FP_t *x = (FP_t *)malloc(sizeof(FP_t) * (M));
	FP_t *b = (FP_t *)malloc(sizeof(FP_t) * (M));
	FP_t inv_sqrt = 1.0 / (M);
	for (int i = 0; i < M; ++i)
		b[i] = inv_sqrt;
	for (int i = 0; i < M; ++i)
		x[i] = 0.0;

	// Run the conjugate gradient
	cg_dense(M, a, b, x, tolerance, itermax, quiet);
	validate_cg_dense(M, a, b, x, tolerance);

	return 0;
}
