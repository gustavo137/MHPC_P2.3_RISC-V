CC=clang
CFLAGS=-O3 -ffast-math -I./sdv_tools
LIBS=-lm

.PHONY: reference-vec.x

codes: reference.x reference-vec.x increase-vec.x increase-vl.x flex-datatype.x
all: codes 

reference.x: src/reference.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

reference-i.x: src/reference-i.c
	$(CC) $(CFLAGS) $(SDV_TRACE_INCL) $^ -o $@ $(LIBS) $(SDV_TRACE_C_LINK)

VFLAGS=-mepi -mllvm -combiner-store-merging=0 -Rpass=loop-vectorize -Rpass-analysis=loop-vectorize -mcpu=avispado -mllvm -vectorizer-use-vp-strided-load-store -mllvm -enable-mem-access-versioning=0 -mllvm -disable-loop-idiom-memcpy -fno-slp-vectorize

reference-vec.x: src/reference-i.c
	$(CC) $(CFLAGS) $(VFLAGS) $(SDV_TRACE_INCL) $^ -o $@ $(LIBS) $(SDV_TRACE_C_LINK)

%.x: src/%.c
	$(CC) $(CFLAGS) $(VFLAGS) $(SDV_TRACE_INCL) $^ -o $@ $(LIBS) $(SDV_TRACE_C_LINK)


clean:
	rm -f *.x

dist_clean:
	rm -rf *.x extrae_prv_traces rave_prv_traces *.out *.trace
