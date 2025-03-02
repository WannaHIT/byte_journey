CC = /usr/bin/gcc 
CFLAGS = -g -Wall -Werror -std=c99 
build:
	$(CC) $(CFLAGS) RISCVInt.c Resource.c MMU.c LoadImage.c Fetch.c \
	Decode.c Execute.c  MemAccess.c WriteBack.c ALUnit.c Branch.c LoadStore.c \
	UpdatePC.c -o RISCVInt

run: build
	./RISCVInt ./loadstore-binary
clean:
	rm -f RISCVEncoder riscv-binary
