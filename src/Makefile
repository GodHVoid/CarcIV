CC=clang
CFLAGS=-O2 -Wall -fPIC -shared -ldl -D_GNU_SOURCE
all: arcIV example

example: example.o arcIV.o
	@sudo $(CC) arcIV.o example.o -o example -Wall -O2

example.o: example.c
	@sudo $(CC) -c -O2 -Wall example.c 

arcIV: arcIV.o
	@sudo $(CC) arcIV.o -o arcIV.so $(CFLAGS)

arcIV.o: arcIV.c 
	@echo "Building Program...."
	@sudo $(CC) -c -O2 -Wall arcIV.c	
	@echo "Done!"

clean:
	@echo "Removing files"
	@sudo rm -f *.o *.so example
