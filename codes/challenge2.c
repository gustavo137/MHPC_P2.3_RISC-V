#include <stdlib.h>
#include <stdio.h>

#include "rave_user_events.h"

// Hint: Do not modify this function
inline double cubeRoot(double n)
{
   double i, precision = 0.1;
   for (i = 1; (i * i * i) <= n; i *= 2)
      ;
   return i;
}
/*
// original code
void Pressure(int N, double *volumes, double *pressures, double *temp, double *new_temp)
{
   rave_event_and_value(1000, 1);
   for (int i = 0; i < N; ++i)
   {
      double length = (volumes[i] > 1.0) ? cubeRoot(volumes[i]) : 0.5;
      pressures[i] = length * 0.25 + (temp[i] - new_temp[i]) * 0.75;
   }
   rave_event_and_value(1000, 0);
}
*/
// my modification
void Pressure(int N, double *volumes, double *pressures, double *temp, double *new_temp)
{
   rave_event_and_value(1000, 1);
   // my code
   // double not_vec[N];// bad idea is veter to reuse pressures
   // not put the 0.25 here because it isnt vectorized
   for (int i = 0; i < N; i++)
   {
      pressures[i] = (volumes[i] > 1.0) ? cubeRoot(volumes[i]) : 0.5;
   }
   // <<<<<<
   for (int i = 0; i < N; ++i)
   {
      // double length = (volumes[i]>1.0) ? cubeRoot(volumes[i]) : 0.5;
      // pressures[i] = length*0.25 + (temp[i]-new_temp[i])*0.75;
      pressures[i] = pressures[i] * 0.25 + (temp[i] - new_temp[i]) * 0.75;
   }
   rave_event_and_value(1000, 0);
}

// Don't edit the main function!
int main()
{
   rave_name_event(1000, "code_region");
   rave_name_value(1000, 0, "Other");
   rave_name_value(1000, 1, "Pressure");

   int N = 4096;
   double *volumes = (double *)malloc(sizeof(double) * N);
   double *pressures = (double *)malloc(sizeof(double) * N);
   double *temp = (double *)malloc(sizeof(double) * N);
   double *new_temp = (double *)malloc(sizeof(double) * N);

   for (int i = 0; i < N; ++i)
   {
      volumes[i] = i * 5.0 / (N * 6.0);
      temp[i] = i;
      new_temp[i] = i + 4.0;
   }

   Pressure(N, volumes, pressures, temp, new_temp);

   for (int i = 0; i < N; ++i)
   {
      double expected = ((volumes[i] > 1.0) ? cubeRoot(volumes[i]) : 0.5) * 0.25 + (temp[i] - new_temp[i]) * 0.75;
      if (pressures[i] != expected)
      {
         printf("Incorrect Result!\n");
         exit(-1);
      }
   }
   printf("Correct result!\n");
}