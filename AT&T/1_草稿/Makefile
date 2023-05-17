out: target.o
	ld -o target.out -dynamic-linker /lib/x86_64-linux-gnu/ld-linux-x86-64.so.2 -lc /lib/x86_64-linux-gnu/crt1.o /lib/x86_64-linux-gnu/crti.o /lib/x86_64-linux-gnu/crtn.o target.o -l:libc.a -L /lib/x86_64-linux-gnu

target.o: target.s
	as target.s -o $@

clean:
	rm target.out* target.o
