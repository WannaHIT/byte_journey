CC = /usr/bin/gcc 
CFLAGS = -g -Wall -Werror -std=c99
build:
	$(CC) $(CFLAGS) overflow.c -o overflow
test: overflow
	./overflow 1 2
	./overflow 1 ffffffff
	./overflow 1 7fffffff
	./overflow 80000000  80000000
clean:
	rm -f overflow
