TARGETS = avx512.sp avx512.dp avx2.sp avx2.dp x86.sp x86.dp x86.int64 x86.int64+st

CC     = icx
CFLAGS = -Ofast -mtune=sapphirerapids -lpapi
