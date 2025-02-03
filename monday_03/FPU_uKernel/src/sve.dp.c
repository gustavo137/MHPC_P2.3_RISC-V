const unsigned long long NINSTR = 32;
const unsigned long long NFPOPS = NINSTR * 16;

void work() {
  asm("fmla     z0.d, p0/m,  z0.d,  z0.d;"
      "fmla     z1.d, p0/m,  z1.d,  z1.d;"
      "fmla     z2.d, p0/m,  z2.d,  z2.d;"
      "fmla     z3.d, p0/m,  z3.d,  z3.d;"
      "fmla     z4.d, p0/m,  z4.d,  z4.d;"
      "fmla     z5.d, p0/m,  z5.d,  z5.d;"
      "fmla     z6.d, p0/m,  z6.d,  z6.d;"
      "fmla     z7.d, p0/m,  z7.d,  z7.d;"

      "fmla     z8.d, p0/m,  z8.d,  z8.d;"
      "fmla     z9.d, p0/m,  z9.d,  z9.d;"
      "fmla    z10.d, p0/m, z10.d, z10.d;"
      "fmla    z11.d, p0/m, z11.d, z11.d;"
      "fmla    z12.d, p0/m, z12.d, z12.d;"
      "fmla    z13.d, p0/m, z13.d, z13.d;"
      "fmla    z14.d, p0/m, z14.d, z14.d;"
      "fmla    z15.d, p0/m, z15.d, z15.d;"

      "fmla    z16.d, p0/m, z16.d, z16.d;"
      "fmla    z17.d, p0/m, z17.d, z17.d;"
      "fmla    z18.d, p0/m, z18.d, z18.d;"
      "fmla    z19.d, p0/m, z19.d, z19.d;"
      "fmla    z20.d, p0/m, z20.d, z20.d;"
      "fmla    z21.d, p0/m, z21.d, z21.d;"
      "fmla    z22.d, p0/m, z22.d, z22.d;"
      "fmla    z23.d, p0/m, z23.d, z23.d;"

      "fmla    z24.d, p0/m, z24.d, z24.d;"
      "fmla    z25.d, p0/m, z25.d, z25.d;"
      "fmla    z26.d, p0/m, z26.d, z26.d;"
      "fmla    z27.d, p0/m, z27.d, z27.d;"
      "fmla    z28.d, p0/m, z28.d, z28.d;"
      "fmla    z29.d, p0/m, z29.d, z29.d;"
      "fmla    z30.d, p0/m, z30.d, z30.d;"
      "fmla    z31.d, p0/m, z31.d, z31.d;"
  );
}
