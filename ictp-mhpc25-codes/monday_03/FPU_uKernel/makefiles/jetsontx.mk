TARGETS = aarch64.dp aarch64.sp neon.dp neon.sp

CC     = gcc
CFLAGS = -O2 -mcpu=native $(PAPI_INCL) $(PAPI_LIBS) -lpapi
