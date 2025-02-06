#include "utils.h"

const unsigned long long NINSTR = 10 * 16;
const unsigned long long NFPOPS = NINSTR * 8;

void work() {
  REPEAT10(
    asm(/*"FMLA  V0.4S, V0.4S, V0.4S;"
        "FMLA  V1.4S, V1.4S, V1.4S;"
        "FMLA  V2.4S, V2.4S, V2.4S;"
        "FMLA  V3.4S, V3.4S, V3.4S;"
        "FMLA  V4.4S, V4.4S, V4.4S;"
        "FMLA  V5.4S, V5.4S, V5.4S;"
        "FMLA  V6.4S, V6.4S, V6.4S;"
        "FMLA  V7.4S, V7.4S, V7.4S;"
  
        "FMLA  V8.4S, V8.4S, V8.4S;"
        "FMLA  V9.4S, V9.4S, V9.4S;"
        "FMLA V10.4S,V10.4S,V10.4S;"
        "FMLA V11.4S,V11.4S,V11.4S;"
        "FMLA V12.4S,V12.4S,V12.4S;"
        "FMLA V13.4S,V13.4S,V13.4S;"
        "FMLA V14.4S,V14.4S,V14.4S;"
        "FMLA V15.4S,V15.4S,V15.4S;"*/
  
        "FMLA V16.4S,V16.4S,V16.4S;"
        "FMLA V17.4S,V17.4S,V17.4S;"
        "FMLA V18.4S,V18.4S,V18.4S;"
        "FMLA V19.4S,V19.4S,V19.4S;"
        "FMLA V20.4S,V20.4S,V20.4S;"
        "FMLA V21.4S,V21.4S,V21.4S;"
        "FMLA V22.4S,V22.4S,V22.4S;"
        "FMLA V23.4S,V23.4S,V23.4S;"
  
        "FMLA V24.4S,V24.4S,V24.4S;"
        "FMLA V25.4S,V25.4S,V25.4S;"
        "FMLA V26.4S,V26.4S,V26.4S;"
        "FMLA V27.4S,V27.4S,V27.4S;"
        "FMLA V28.4S,V28.4S,V28.4S;"
        "FMLA V29.4S,V29.4S,V29.4S;"
        "FMLA V30.4S,V30.4S,V30.4S;"
        "FMLA V31.4S,V31.4S,V31.4S;"
    );
  )
}
