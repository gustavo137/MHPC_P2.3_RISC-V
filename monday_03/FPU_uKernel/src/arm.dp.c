const unsigned long long NINSTR = 32;
const unsigned long long NFPOPS = NINSTR * 2;

void work() {
  asm("VFMA.F64  D0, D0, D0;"
      "VFMA.F64  D1, D1, D1;"
      "VFMA.F64  D2, D2, D2;"
      "VFMA.F64  D3, D3, D3;"
      "VFMA.F64  D4, D4, D4;"
      "VFMA.F64  D5, D5, D5;"
      "VFMA.F64  D6, D6, D6;"
      "VFMA.F64  D7, D7, D7;"

      "VFMA.F64  D8, D8, D8;"
      "VFMA.F64  D9, D9, D9;"
      "VFMA.F64 D10,D10,D10;"
      "VFMA.F64 D11,D11,D11;"
      "VFMA.F64 D12,D12,D12;"
      "VFMA.F64 D13,D13,D13;"
      "VFMA.F64 D14,D14,D14;"
      "VFMA.F64 D15,D15,D15;"

      "VFMA.F64 D16,D16,D16;"
      "VFMA.F64 D17,D17,D17;"
      "VFMA.F64 D18,D18,D18;"
      "VFMA.F64 D19,D19,D19;"
      "VFMA.F64 D20,D20,D20;"
      "VFMA.F64 D21,D21,D21;"
      "VFMA.F64 D22,D22,D22;"
      "VFMA.F64 D23,D23,D23;"

      "VFMA.F64 D24,D24,D24;"
      "VFMA.F64 D25,D25,D25;"
      "VFMA.F64 D26,D26,D26;"
      "VFMA.F64 D27,D27,D27;"
      "VFMA.F64 D28,D28,D28;"
      "VFMA.F64 D29,D29,D29;"
      "VFMA.F64 D30,D30,D30;"
      "VFMA.F64 D31,D31,D31;"
  );
}
