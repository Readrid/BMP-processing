.PHONY: all clean

CFLAGS=-Wall -Wextra -Werror -g -I include

all: bmp-processing

clean:
	rm -rf obj hw_01
obj:
	mkdir obj
obj/main.o: src/main.c | obj
	gcc $(CFLAGS) -c src/main.c -o obj/main.o
obj/bmp.o: src/bmp.c | obj
	gcc $(CFLAGS) -c src/bmp.c -o obj/bmp.o
bmp-processing: obj/main.o obj/bmp.o
	gcc $(CFLAGS) obj/main.o obj/bmp.o -o bmp-processing
