const unsigned long long NINSTR = 32;
const unsigned long long NFPOPS = NINSTR * 32;

void work() {
  asm("fmla     z0.s, p1/m,  z0.s,  z0.s;"
      "fmla     z1.s, p1/m,  z1.s,  z1.s;"
      "fmla     z2.s, p1/m,  z2.s,  z2.s;"
      "fmla     z3.s, p1/m,  z3.s,  z3.s;"
      "fmla     z4.s, p1/m,  z4.s,  z4.s;"
      "fmla     z5.s, p1/m,  z5.s,  z5.s;"
      "fmla     z6.s, p1/m,  z6.s,  z6.s;"
      "fmla     z7.s, p1/m,  z7.s,  z7.s;"

      "fmla     z8.s, p1/m,  z8.s,  z8.s;"
      "fmla     z9.s, p1/m,  z9.s,  z9.s;"
      "fmla    z10.s, p1/m, z10.s, z10.s;"
      "fmla    z11.s, p1/m, z11.s, z11.s;"
      "fmla    z12.s, p1/m, z12.s, z12.s;"
      "fmla    z13.s, p1/m, z13.s, z13.s;"
      "fmla    z14.s, p1/m, z14.s, z14.s;"
      "fmla    z15.s, p1/m, z15.s, z15.s;"

      "fmla    z16.s, p1/m, z16.s, z16.s;"
      "fmla    z17.s, p1/m, z17.s, z17.s;"
      "fmla    z18.s, p1/m, z18.s, z18.s;"
      "fmla    z19.s, p1/m, z19.s, z19.s;"
      "fmla    z20.s, p1/m, z20.s, z20.s;"
      "fmla    z21.s, p1/m, z21.s, z21.s;"
      "fmla    z22.s, p1/m, z22.s, z22.s;"
      "fmla    z23.s, p1/m, z23.s, z23.s;"

      "fmla    z24.s, p1/m, z24.s, z24.s;"
      "fmla    z25.s, p1/m, z25.s, z25.s;"
      "fmla    z26.s, p1/m, z26.s, z26.s;"
      "fmla    z27.s, p1/m, z27.s, z27.s;"
      "fmla    z28.s, p1/m, z28.s, z28.s;"
      "fmla    z29.s, p1/m, z29.s, z29.s;"
      "fmla    z30.s, p1/m, z30.s, z30.s;"
      "fmla    z31.s, p1/m, z31.s, z31.s;"
  );
}
