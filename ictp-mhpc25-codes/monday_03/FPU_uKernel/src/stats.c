#include "stats.h"

#include <math.h>

double sum(double *v, size_t elem) {
  size_t i;
  double res = 0.0;

  for (i = 0; i < elem; i++) {
    res += v[i];
  }

  return res;
}

double max(double *v, size_t elem) {
  size_t i;
  double res = v[0];

  for (i = 1; i < elem; i++) {
    res = res >= v[i] ? res : v[i];
  }

  return res;
}

double min(double *v, size_t elem) {
  size_t i;
  double res = v[0];

  for (i = 1; i < elem; i++) {
    res = res < v[i] ? res : v[i];
  }

  return res;
}

double std(double *v, size_t elem) {
  size_t i;
  double avg = sum(v, elem) / (double)elem;
  double res = 0;

  for (i = 0; i < elem; ++i) {
    res += (v[i] - avg)*(v[i] - avg);
  }

  res = sqrt(res * 1.0/(double)(elem - 1));

  return res;
}
