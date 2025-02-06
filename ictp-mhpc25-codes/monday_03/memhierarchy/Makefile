all: MemHierarchy

arch=$(shell arch)

MemHierarchy: MemHierarchy.c
	gcc -O3 -I. $^ -o $@-$(arch).x 

clean:
	rm *.x
