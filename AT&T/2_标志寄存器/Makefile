of: of.s
	as of.s -o of.o
	gcc of.o -o of.out

of-n: of-n.s
	as of-n.s -o of-n.o
	gcc of-n.o -o of-n.out

pf: pf.s
	as -o $@.o $@.s
	gcc -o $@.out $@.o

af: af.s
	gcc -o $@.o -c $@.s -m32
	ld $@.o -o $@.out -melf_i386 -e main

zf: zf.s
	as -o $@.o $@.s
	gcc -o $@.out $@.o

if: if.s
	as -o $@.o $@.s
	gcc -o $@.out $@.o

sf: sf.s
	as -o $@.o $@.s
	gcc -o $@.out $@.o