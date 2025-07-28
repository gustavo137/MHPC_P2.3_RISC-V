#include "utils.h"

const unsigned long long NINSTR = 10 * 16;
const unsigned long long NFPOPS = NINSTR * 2;

void work() {
  REPEAT10(
    asm(/*"FMADD  D0, D0, D0, D0;"
        "FMADD  D1, D1, D1, D1;"
        "FMADD  D2, D2, D2, D2;"
        "FMADD  D3, D3, D3, D3;"
        "FMADD  D4, D4, D4, D4;"
        "FMADD  D5, D5, D5, D5;"
        "FMADD  D6, D6, D6, D6;"
        "FMADD  D7, D7, D7, D7;"
  
        "FMADD  D8, D8, D8, D8;"
        "FMADD  D9, D9, D9, D9;"
        "FMADD D10,D10,D10,D10;"
        "FMADD D11,D11,D11,D11;"
        "FMADD D12,D12,D12,D12;"
        "FMADD D13,D13,D13,D13;"
        "FMADD D14,D14,D14,D14;"
        "FMADD D15,D15,D15,D15;"*/
                              
        "FMADD D16,D16,D16,D16;"
        "FMADD D17,D17,D17,D17;"
        "FMADD D18,D18,D18,D18;"
        "FMADD D19,D19,D19,D19;"
        "FMADD D20,D20,D20,D20;"
        "FMADD D21,D21,D21,D21;"
        "FMADD D22,D22,D22,D22;"
        "FMADD D23,D23,D23,D23;"
                              
        "FMADD D24,D24,D24,D24;"
        "FMADD D25,D25,D25,D25;"
        "FMADD D26,D26,D26,D26;"
        "FMADD D27,D27,D27,D27;"
        "FMADD D28,D28,D28,D28;"
        "FMADD D29,D29,D29,D29;"
        "FMADD D30,D30,D30,D30;"
        "FMADD D31,D31,D31,D31;"
    );
  )
}
