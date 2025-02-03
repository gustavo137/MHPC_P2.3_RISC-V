#include "utils.h"

const unsigned long long NINSTR = 10 * 16;
const unsigned long long NFPOPS = NINSTR * 2;

void work() {
  REPEAT10(
    asm("FMADD.D f16,f16,f16,f16;"
        "FMADD.D f17,f17,f17,f17;"
        "FMADD.D f18,f18,f18,f18;"
        "FMADD.D f19,f19,f19,f19;"
        "FMADD.D f20,f20,f20,f20;"
        "FMADD.D f21,f21,f21,f21;"
        "FMADD.D f22,f22,f22,f22;"
        "FMADD.D f23,f23,f23,f23;"
                                
        "FMADD.D f24,f24,f24,f24;"
        "FMADD.D f25,f25,f25,f25;"
        "FMADD.D f26,f26,f26,f26;"
        "FMADD.D f27,f27,f27,f27;"
        "FMADD.D f28,f28,f28,f28;"
        "FMADD.D f29,f29,f29,f29;"
        "FMADD.D f30,f30,f30,f30;"
        "FMADD.D f31,f31,f31,f31;"
    );
  )
}
