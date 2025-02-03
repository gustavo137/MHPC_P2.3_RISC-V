#include "utils.h"

const unsigned long long NINSTR = 10 * 16;
const unsigned long long NFPOPS = NINSTR * 2;

void work() {
  REPEAT10(
    asm(/*"FMADD  S0, S0, S0, S0;"
        "FMADD  S1, S1, S1, S1;"
        "FMADD  S2, S2, S2, S2;"
        "FMADD  S3, S3, S3, S3;"
        "FMADD  S4, S4, S4, S4;"
        "FMADD  S5, S5, S5, S5;"
        "FMADD  S6, S6, S6, S6;"
        "FMADD  S7, S7, S7, S7;"
                              
        "FMADD  S8, S8, S8, S8;"
        "FMADD  S9, S9, S9, S9;"
        "FMADD S10,S10,S10,S10;"
        "FMADD S11,S11,S11,S11;"
        "FMADD S12,S12,S12,S12;"
        "FMADD S13,S13,S13,S13;"
        "FMADD S14,S14,S14,S14;"
        "FMADD S15,S15,S15,S15;"*/
                              
        "FMADD S16,S16,S16,S16;"
        "FMADD S17,S17,S17,S17;"
        "FMADD S18,S18,S18,S18;"
        "FMADD S19,S19,S19,S19;"
        "FMADD S20,S20,S20,S20;"
        "FMADD S21,S21,S21,S21;"
        "FMADD S22,S22,S22,S22;"
        "FMADD S23,S23,S23,S23;"
                              
        "FMADD S24,S24,S24,S24;"
        "FMADD S25,S25,S25,S25;"
        "FMADD S26,S26,S26,S26;"
        "FMADD S27,S27,S27,S27;"
        "FMADD S28,S28,S28,S28;"
        "FMADD S29,S29,S29,S29;"
        "FMADD S30,S30,S30,S30;"
        "FMADD S31,S31,S31,S31;"
    );
  )
}
