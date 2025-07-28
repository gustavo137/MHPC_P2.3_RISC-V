all: gemm

arch=$(shell arch)

gemm: gemm.c
	gcc -O3 $^ -o $@-$(arch).x 

clean:
	rm *.x
