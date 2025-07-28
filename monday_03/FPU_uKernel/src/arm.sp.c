const unsigned long long NINSTR = 32;
const unsigned long long NFPOPS = NINSTR * 2;

void work() {
  asm("VFMA.F32  S0, S0, S0;"
      "VFMA.F32  S1, S1, S1;"
      "VFMA.F32  S2, S2, S2;"
      "VFMA.F32  S3, S3, S3;"
      "VFMA.F32  S4, S4, S4;"
      "VFMA.F32  S5, S5, S5;"
      "VFMA.F32  S6, S6, S6;"
      "VFMA.F32  S7, S7, S7;"

      "VFMA.F32  S8, S8, S8;"
      "VFMA.F32  S9, S9, S9;"
      "VFMA.F32 S10,S10,S10;"
      "VFMA.F32 S11,S11,S11;"
      "VFMA.F32 S12,S12,S12;"
      "VFMA.F32 S13,S13,S13;"
      "VFMA.F32 S14,S14,S14;"
      "VFMA.F32 S15,S15,S15;"

      "VFMA.F32 S16,S16,S16;"
      "VFMA.F32 S17,S17,S17;"
      "VFMA.F32 S18,S18,S18;"
      "VFMA.F32 S19,S19,S19;"
      "VFMA.F32 S20,S20,S20;"
      "VFMA.F32 S21,S21,S21;"
      "VFMA.F32 S22,S22,S22;"
      "VFMA.F32 S23,S23,S23;"

      "VFMA.F32 S24,S24,S24;"
      "VFMA.F32 S25,S25,S25;"
      "VFMA.F32 S26,S26,S26;"
      "VFMA.F32 S27,S27,S27;"
      "VFMA.F32 S28,S28,S28;"
      "VFMA.F32 S29,S29,S29;"
      "VFMA.F32 S30,S30,S30;"
      "VFMA.F32 S31,S31,S31;"
  );
}
