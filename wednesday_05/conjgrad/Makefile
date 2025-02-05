all: cg

IFLAGS=$(SDV_TRACE_INCL)
LDFLAGS=$(SDV_TRACE_C_LINK)

CC=clang
CFLAGS=-O3 -fno-vectorize

CFLAGS_OPT=-O3 -ffast-math -mepi -mcpu=avispado -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize -mllvm -vectorizer-use-vp-strided-load-store -mllvm -disable-loop-idiom-memcpy -mllvm -combiner-store-merging=0 -fno-slp-vectorize -mllvm -enable-mem-access-versioning=0 #... Add vectorization flags here!

cg-opt: cg.c
	$(CC) $(CFLAGS_OPT) $(IFLAGS) $^ -o $@.x $(LDFLAGS)

cg: cg.c
	$(CC) $(CFLAGS) $(IFLAGS) -fno-vectorize $^ -o $@.x $(LDFLAGS)

clean:
	rm -f *.x

