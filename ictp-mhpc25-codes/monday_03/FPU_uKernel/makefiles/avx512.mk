TARGETS = avx512.sp avx512.dp

# MareNostrum4
CC     ?= icc
CFLAGS ?= -xCORE-AVX512 -mtune=skylake
