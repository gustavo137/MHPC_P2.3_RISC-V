#include "utils.h"

const unsigned long long NINSTR = 10 * 16;
const unsigned long long NFPOPS = NINSTR * 4;

void work() {
  REPEAT10(
    asm(/*"FMLA  V0.2D, V0.2D, V0.2D;"
        "FMLA  V1.2D, V1.2D, V1.2D;"
        "FMLA  V2.2D, V2.2D, V2.2D;"
        "FMLA  V3.2D, V3.2D, V3.2D;"
        "FMLA  V4.2D, V4.2D, V4.2D;"
        "FMLA  V5.2D, V5.2D, V5.2D;"
        "FMLA  V6.2D, V6.2D, V6.2D;"
        "FMLA  V7.2D, V7.2D, V7.2D;"
  
        "FMLA  V8.2D, V8.2D, V8.2D;"
        "FMLA  V9.2D, V9.2D, V9.2D;"
        "FMLA V10.2D,V10.2D,V10.2D;"
        "FMLA V11.2D,V11.2D,V11.2D;"
        "FMLA V12.2D,V12.2D,V12.2D;"
        "FMLA V13.2D,V13.2D,V13.2D;"
        "FMLA V14.2D,V14.2D,V14.2D;"
        "FMLA V15.2D,V15.2D,V15.2D;"*/
  
        "FMLA V16.2D,V16.2D,V16.2D;"
        "FMLA V17.2D,V17.2D,V17.2D;"
        "FMLA V18.2D,V18.2D,V18.2D;"
        "FMLA V19.2D,V19.2D,V19.2D;"
        "FMLA V20.2D,V20.2D,V20.2D;"
        "FMLA V21.2D,V21.2D,V21.2D;"
        "FMLA V22.2D,V22.2D,V22.2D;"
        "FMLA V23.2D,V23.2D,V23.2D;"
  
        "FMLA V24.2D,V24.2D,V24.2D;"
        "FMLA V25.2D,V25.2D,V25.2D;"
        "FMLA V26.2D,V26.2D,V26.2D;"
        "FMLA V27.2D,V27.2D,V27.2D;"
        "FMLA V28.2D,V28.2D,V28.2D;"
        "FMLA V29.2D,V29.2D,V29.2D;"
        "FMLA V30.2D,V30.2D,V30.2D;"
        "FMLA V31.2D,V31.2D,V31.2D;"
    );
  )
}
