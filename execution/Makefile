CC = ~/riscv/bin/riscv64-unknown-elf-gcc
CFALGS = -g -Wall -Werror -std=c99 -march=rv32im -mabi=ilp32  -Wno-error=main -Wno-error=return-mismatch
OBJDUMP = ~/riscv/bin/riscv64-unknown-elf-objdump

build:
	$(CC) $(CFALGS) Empty.c -o empty 
	$(CC) $(CFALGS) CallStack.c -o callstack 
	$(CC) $(CFALGS) LocallCall.c -o locallcall 
	$(CC) $(CFALGS) NoHello.c -o nohello
	$(CC) $(CFALGS) Params2Call.c -o params2
	$(CC) $(CFALGS) ParamsStruct.c -o parstruct
	$(CC) $(CFALGS) Params9Call.c -o params9
	$(CC) $(CFALGS) CallReturn.c -o callret
