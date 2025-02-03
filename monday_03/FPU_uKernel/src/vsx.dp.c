const unsigned long long NINSTR = 32;
const unsigned long long NFPOPS = NINSTR * 4;

void work() {
  asm("xvmaddadp  0, 0, 0;"
      "xvmaddadp  1, 1, 1;"
      "xvmaddadp  2, 2, 2;"
      "xvmaddadp  3, 3, 3;"
      "xvmaddadp  4, 4, 4;"
      "xvmaddadp  5, 5, 5;"
      "xvmaddadp  6, 6, 6;"
      "xvmaddadp  7, 7, 7;"

      "xvmaddadp  8, 8, 8;"
      "xvmaddadp  9, 9, 9;"
      "xvmaddadp 10,10,10;"
      "xvmaddadp 11,11,11;"
      "xvmaddadp 12,12,12;"
      "xvmaddadp 13,13,13;"
      "xvmaddadp 14,14,14;"
      "xvmaddadp 15,15,15;"

      "xvmaddadp 16,16,16;"
      "xvmaddadp 17,17,17;"
      "xvmaddadp 18,18,18;"
      "xvmaddadp 19,19,19;"
      "xvmaddadp 20,20,20;"
      "xvmaddadp 21,21,21;"
      "xvmaddadp 22,22,22;"
      "xvmaddadp 23,23,23;"

      "xvmaddadp 24,24,24;"
      "xvmaddadp 25,25,25;"
      "xvmaddadp 26,26,26;"
      "xvmaddadp 27,27,27;"
      "xvmaddadp 28,28,28;"
      "xvmaddadp 29,29,29;"
      "xvmaddadp 30,30,30;"
      "xvmaddadp 31,31,31;"
  );  
}
