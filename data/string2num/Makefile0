CC = /usr/bin/gcc 
CFLAGS = -g -Wall -Werror -std=c99
build:
	$(CC) $(CFLAGS) string2num.c -o strnum 

test: strnum
	./strnum "1"
	./strnum "2147483647"
	./strnum "2147483648"
	./strnum "-1"
	./strnum "-1234"
	./strnum "-2147483648"
	./strnum "0xaBcD"
	./strnum "    abcd1234 abcd"
	./strnum "-0xabcd"
	./strnum "0xfffffffff"
	./strnum "-0x80000000"
	./strnum "-0xfffffffff"
	./strnum "    1234"
	./strnum "    1234abcd"
	./strnum "0x1234abcd"
	./strnum "0xabcdhello world"
	./strnum "NOT a number"

clean:
	rm -f strnum
