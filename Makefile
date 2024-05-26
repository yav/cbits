.PHONY: clean default

default: main


large_bits.o: large_bits.c large_bits.h Makefile
	gcc -Wall -c -o $@ $<

main: main.c small_bits.h large_bits.o Makefile
	gcc -Wall -o $@ $< large_bits.o


clean:
	rm -rf *.o

