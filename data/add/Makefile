CC = gcc
CFLAGS = -Wall -Werror -std=c99
SRC = $(wildcard *.c)
TARGET = adder32

$(TARGET):$(SRC)
	$(CC) $(CFALGS) $< -o $@

test: adder32 
	./adder32 1 2
	./adder32 7 7
	./adder32 2147483648 1
	./adder32 4294967295 0
	./adder32 4294967495 1
	./adder32 2147483647 1
	./adder32 2147483647 0
	./adder32 2147483648 4294967295
	./adder32 2147483648 2147483648

.PHONY: clean
clean:
	rm -f adder32