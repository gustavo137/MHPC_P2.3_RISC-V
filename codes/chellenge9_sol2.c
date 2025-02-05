#include <stdio.h>

#include "rave_user_events.h"
#define V_LEN 2048

class Vector
{
public:
   double elements[V_LEN];
   Vector() { ; }
   Vector(double *values)
   {
      for (int i = 0; i < V_LEN; ++i)
         elements[i] = values[i];
   }
   Vector(double broadcast)
   {
      for (int i = 0; i < V_LEN; ++i)
         elements[i] = broadcast;
   }
};

// Hint: Most changes can be made here!
/*
inline Vector add_vector(Vector & A, Vector & B){
    Vector res;
    for(int i=0; i<V_LEN; ++i) res.elements[i] = A.elements[i] + B.elements[i];
    return res;
}
inline Vector sub_vector(Vector & A, Vector & B){
    Vector res;
    for(int i=0; i<V_LEN; ++i) res.elements[i] = A.elements[i] - B.elements[i];
    return res;
}
inline Vector mul_vector(Vector & A, Vector & B){
    Vector res;
    for(int i=0; i<V_LEN; ++i) res.elements[i] = A.elements[i] * B.elements[i];
    return res;
}
*/

void VectorOps(Vector &A, Vector &B, Vector &C, Vector &D)
{
   rave_event_and_value(1000, 1);
#pragma clang loop vectorize(assume_safety)
   for (int i = 0; i < V_LEN; ++i)
   {
      double r1 = A.elements[i] + C.elements[i];
      double r2 = A.elements[i] * B.elements[i];
      double r3 = C.elements[i] - r2;
      D.elements[i] = r1 + r3;
   }
   rave_event_and_value(1000, 0);
}

// Don't edit the main function!
int main()
{
   rave_name_event(1000, "code_region");
   rave_name_value(1000, 0, "Other");
   rave_name_value(1000, 1, "Vector_Ops");

   Vector A(42.0);
   Vector B(3.14);
   Vector C(1.0);
   Vector D(0.0);

   VectorOps(A, B, C, D);

   double diff = D.elements[42] - (43.0 + ((1.0) - (42.0 * 3.14)));
   if (diff * diff > 1e-3)
   {
      printf("Incorrect result\n");
      exit(-1);
   }
   printf("Correct!\n");

   return 0;
}
