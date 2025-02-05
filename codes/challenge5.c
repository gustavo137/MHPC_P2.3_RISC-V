#include <stdlib.h>
#include <stdio.h>

#include "rave_user_events.h"

// Constant N to simplify the challenge. Feel free to make it variable!
#define N 4096

struct Complex
{
   double real;
   double imag;
};
typedef struct Complex Complex;
Complex X[N];
Complex Y[N];

// Remember to reimplement these three functions if you change the Complex structure!
void Initialize(double r, double i, double r2, double i2)
{
   for (int j = 0; j < N; ++j)
   {
      X[j].real = r;
      X[j].imag = i;
      Y[j].real = r2;
      Y[j].imag = i2;
   }
}
double check_result_real(int index)
{
   return Y[index].real;
}
double check_result_imag(int index)
{
   return Y[index].imag;
}

void C_axpy(double alpha_r, double alpha_i)
{
   rave_event_and_value(1000, 1);
   for (int i = 0; i < N; ++i)
   {
      Y[i].real = Y[i].real + X[i].real * alpha_r - X[i].imag * alpha_i;
      Y[i].imag = Y[i].imag + X[i].real * alpha_i + X[i].imag * alpha_r;
   }
   rave_event_and_value(1000, 0);
}

// Don't touch the main function!
int main()
{
   rave_name_event(1000, "code_region");
   rave_name_value(1000, 0, "Other");
   rave_name_value(1000, 1, "StartEnd");

   double alpha_r = 42.0;
   double alpha_i = 3.14;
   Initialize(32.0, 2.0, 0.0, 0.0);

   C_axpy(alpha_r, alpha_i);

   for (int i = 0; i < N; ++i)
   {
      double diff = check_result_real(i) - (32.0 * 42.0 - 2.0 * 3.14);
      double diff1 = check_result_imag(i) - (32.0 * 3.14 + 2.0 * 42.0);
      if (diff * diff > 1e3 || diff1 * diff > 1e3)
      {
         printf("Incorrect Result!\n");
         exit(-1);
      }
   }
   printf("Correct!\n");

   return 0;
}
