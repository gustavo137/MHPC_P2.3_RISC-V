all: buffcopy

arch=$(shell arch)

buffcopy: buffcopy.c
	gcc -O3 -I. $^ -o $@-$(arch).x 

clean:
	rm -f	*.x
