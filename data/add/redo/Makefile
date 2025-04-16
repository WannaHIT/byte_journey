CC = gcc
CFLAGS = -Wall -Werror -std=c99
SRC = $(wildcard *.c)
TARGET = adder4

$(TARGET):$(SRC)
	$(CC) $(CFALGS) $< -o $@

test: adder4
	./adder4 1 6 
	./adder4 2 6 
	./adder4 7 7
	./adder4 8 8 
	./adder4 12 3
	./adder4 15 0
	./adder4 15 15


.PHONY: clean
clean:
	rm -f adder4