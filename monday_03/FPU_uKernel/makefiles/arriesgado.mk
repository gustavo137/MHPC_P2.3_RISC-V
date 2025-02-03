TARGETS = riscv.dp riscv.sp

CC      = gcc
CFLAGS  = -O2 -march=rv64gc $(PAPI_INCL)
LDFLAGS = $(PAPI_LIBS) -lpapi
