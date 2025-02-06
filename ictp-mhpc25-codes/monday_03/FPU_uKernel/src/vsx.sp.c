const unsigned long long NINSTR = 32;
const unsigned long long NFPOPS = NINSTR * 8;

void work() {
  asm("xvmaddasp  0, 0, 0;"
      "xvmaddasp  1, 1, 1;"
      "xvmaddasp  2, 2, 2;"
      "xvmaddasp  3, 3, 3;"
      "xvmaddasp  4, 4, 4;"
      "xvmaddasp  5, 5, 5;"
      "xvmaddasp  6, 6, 6;"
      "xvmaddasp  7, 7, 7;"

      "xvmaddasp  8, 8, 8;"
      "xvmaddasp  9, 9, 9;"
      "xvmaddasp 10,10,10;"
      "xvmaddasp 11,11,11;"
      "xvmaddasp 12,12,12;"
      "xvmaddasp 13,13,13;"
      "xvmaddasp 14,14,14;"
      "xvmaddasp 15,15,15;"

      "xvmaddasp 16,16,16;"
      "xvmaddasp 17,17,17;"
      "xvmaddasp 18,18,18;"
      "xvmaddasp 19,19,19;"
      "xvmaddasp 20,20,20;"
      "xvmaddasp 21,21,21;"
      "xvmaddasp 22,22,22;"
      "xvmaddasp 23,23,23;"

      "xvmaddasp 24,24,24;"
      "xvmaddasp 25,25,25;"
      "xvmaddasp 26,26,26;"
      "xvmaddasp 27,27,27;"
      "xvmaddasp 28,28,28;"
      "xvmaddasp 29,29,29;"
      "xvmaddasp 30,30,30;"
      "xvmaddasp 31,31,31;"
  );  
}
