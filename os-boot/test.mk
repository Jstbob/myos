main.out: link.ld main.c
	gcc main.c -o main.out -T link.ld -g

main.o: main.c
	gcc -c main.c -g
	ld main.o -T link.ld -g -o main.out
