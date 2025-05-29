CC = /usr/bin/gcc 
CFLAGS = -g -Wall -Werror -std=c99
SRC = string2num.c 
TARGET = strnum
# build:
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

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
	./strnum "00xa"
	./strnum "0-"
	./strnum "-a"
	./strnum "0a"
	./strnum "00"
	./strnum "a"
	./strnum "-0xa"
	./strnum "0x"
	./strnum "5-"

.PHONY: clean 
clean:
	rm -f $(TARGET)
