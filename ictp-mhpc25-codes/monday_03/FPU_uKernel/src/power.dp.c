const unsigned long long NINSTR = 32;
const unsigned long long NFPOPS = NINSTR * 2;

void work() {
  asm("fmul  0, 0, 0;"
      "fmul  1, 1, 1;"
      "fmul  2, 2, 2;"
      "fmul  3, 3, 3;"
      "fmul  4, 4, 4;"
      "fmul  5, 5, 5;"
      "fmul  6, 6, 6;"
      "fmul  7, 7, 7;"

      "fmul  8, 8, 8;"
      "fmul  9, 9, 9;"
      "fmul 10,10,10;"
      "fmul 11,11,11;"
      "fmul 12,12,12;"
      "fmul 13,13,13;"
      "fmul 14,14,14;"
      "fmul 15,15,15;"

      "fmul 16,16,16;"
      "fmul 17,17,17;"
      "fmul 18,18,18;"
      "fmul 19,19,19;"
      "fmul 20,20,20;"
      "fmul 21,21,21;"
      "fmul 22,22,22;"
      "fmul 23,23,23;"

      "fmul 24,24,24;"
      "fmul 25,25,25;"
      "fmul 26,26,26;"
      "fmul 27,27,27;"
      "fmul 28,28,28;"
      "fmul 29,29,29;"
      "fmul 30,30,30;"
      "fmul 31,31,31;"
  );  
}
