CC = /usr/bin/gcc
CFALGS = -Wall -g
SRC = Add.c 
OBJ = Add 
# build: Add 
$(OBJ):$(SRC)
	$(CC) $(CFALGS)  -o $@ $^  

test: Add 
	./Add 1 2
	./Add 8 2
	./Add 88 12
	./Add 99 99 
clean:
	rm -rf Add 
