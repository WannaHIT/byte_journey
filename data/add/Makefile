CC = /usr/bin/gcc 
CFLAGS = -g -Wall -Werror -std=c99
build:
	$(CC) $(CFLAGS) add.c -o add 
test: add 
	./add 1 2
	./add 2147483648 1
	./add 4294967295 0
	./add 4294967495 1
	./add 2147483647 1
	./add 2147483647 0
	./add 2147483648 4294967295
	./add 2147483648 2147483648

clean:
	rm -f add 
