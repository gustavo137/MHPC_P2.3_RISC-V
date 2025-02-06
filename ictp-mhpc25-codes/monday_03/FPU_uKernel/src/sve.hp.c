const unsigned long long NINSTR = 32;
const unsigned long long NFPOPS = NINSTR * 64;

void work() {
  asm("fmla     z0.h, p1/m,  z0.h,  z0.h;"
      "fmla     z1.h, p1/m,  z1.h,  z1.h;"
      "fmla     z2.h, p1/m,  z2.h,  z2.h;"
      "fmla     z3.h, p1/m,  z3.h,  z3.h;"
      "fmla     z4.h, p1/m,  z4.h,  z4.h;"
      "fmla     z5.h, p1/m,  z5.h,  z5.h;"
      "fmla     z6.h, p1/m,  z6.h,  z6.h;"
      "fmla     z7.h, p1/m,  z7.h,  z7.h;"

      "fmla     z8.h, p1/m,  z8.h,  z8.h;"
      "fmla     z9.h, p1/m,  z9.h,  z9.h;"
      "fmla    z10.h, p1/m, z10.h, z10.h;"
      "fmla    z11.h, p1/m, z11.h, z11.h;"
      "fmla    z12.h, p1/m, z12.h, z12.h;"
      "fmla    z13.h, p1/m, z13.h, z13.h;"
      "fmla    z14.h, p1/m, z14.h, z14.h;"
      "fmla    z15.h, p1/m, z15.h, z15.h;"

      "fmla    z16.h, p1/m, z16.h, z16.h;"
      "fmla    z17.h, p1/m, z17.h, z17.h;"
      "fmla    z18.h, p1/m, z18.h, z18.h;"
      "fmla    z19.h, p1/m, z19.h, z19.h;"
      "fmla    z20.h, p1/m, z20.h, z20.h;"
      "fmla    z21.h, p1/m, z21.h, z21.h;"
      "fmla    z22.h, p1/m, z22.h, z22.h;"
      "fmla    z23.h, p1/m, z23.h, z23.h;"

      "fmla    z24.h, p1/m, z24.h, z24.h;"
      "fmla    z25.h, p1/m, z25.h, z25.h;"
      "fmla    z26.h, p1/m, z26.h, z26.h;"
      "fmla    z27.h, p1/m, z27.h, z27.h;"
      "fmla    z28.h, p1/m, z28.h, z28.h;"
      "fmla    z29.h, p1/m, z29.h, z29.h;"
      "fmla    z30.h, p1/m, z30.h, z30.h;"
      "fmla    z31.h, p1/m, z31.h, z31.h;"
  );
}
