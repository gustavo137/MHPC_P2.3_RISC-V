#include "utils.h"

const unsigned long long NINSTR = 10 * 16;
const unsigned long long NFPOPS = NINSTR * 2;

void work() {
  REPEAT10(
    asm("FMADD.S f16,f16,f16,f16;"
        "FMADD.S f17,f17,f17,f17;"
        "FMADD.S f18,f18,f18,f18;"
        "FMADD.S f19,f19,f19,f19;"
        "FMADD.S f20,f20,f20,f20;"
        "FMADD.S f21,f21,f21,f21;"
        "FMADD.S f22,f22,f22,f22;"
        "FMADD.S f23,f23,f23,f23;"
                                
        "FMADD.S f24,f24,f24,f24;"
        "FMADD.S f25,f25,f25,f25;"
        "FMADD.S f26,f26,f26,f26;"
        "FMADD.S f27,f27,f27,f27;"
        "FMADD.S f28,f28,f28,f28;"
        "FMADD.S f29,f29,f29,f29;"
        "FMADD.S f30,f30,f30,f30;"
        "FMADD.S f31,f31,f31,f31;"
    );
  )
}
