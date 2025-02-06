all: cg

IFLAGS=$(SDV_TRACE_INCL)
LDFLAGS=$(SDV_TRACE_C_LINK)

CC=clang
CFLAGS=-O3 -fno-vectorize

CFLAGS_OPT=-O3 #... Add vectorization flags here!

cg-opt: cg.c
	$(CC) $(CFLAGS_OPT) $(IFLAGS) $^ -o $@.x $(LDFLAGS)

cg: cg.c
	$(CC) $(CFLAGS) $(IFLAGS) -fno-vectorize $^ -o $@.x $(LDFLAGS)

clean:
	rm -f *.x

