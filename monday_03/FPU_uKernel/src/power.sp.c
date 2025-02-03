const unsigned long long NINSTR = 32;
const unsigned long long NFPOPS = NINSTR * 2;

void work() {
  asm("fmuls  0, 0, 0;"
      "fmuls  1, 1, 1;"
      "fmuls  2, 2, 2;"
      "fmuls  3, 3, 3;"
      "fmuls  4, 4, 4;"
      "fmuls  5, 5, 5;"
      "fmuls  6, 6, 6;"
      "fmuls  7, 7, 7;"

      "fmuls  8, 8, 8;"
      "fmuls  9, 9, 9;"
      "fmuls 10,10,10;"
      "fmuls 11,11,11;"
      "fmuls 12,12,12;"
      "fmuls 13,13,13;"
      "fmuls 14,14,14;"
      "fmuls 15,15,15;"

      "fmuls 16,16,16;"
      "fmuls 17,17,17;"
      "fmuls 18,18,18;"
      "fmuls 19,19,19;"
      "fmuls 20,20,20;"
      "fmuls 21,21,21;"
      "fmuls 22,22,22;"
      "fmuls 23,23,23;"

      "fmuls 24,24,24;"
      "fmuls 25,25,25;"
      "fmuls 26,26,26;"
      "fmuls 27,27,27;"
      "fmuls 28,28,28;"
      "fmuls 29,29,29;"
      "fmuls 30,30,30;"
      "fmuls 31,31,31;"
  );  
}
