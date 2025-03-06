#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
// make -f Makefile build
// ./Bin input.txt output.bin

// 将txt文件里面十六进制指令的文本文件 转换为 二进制文件
int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		return 0;
	}
	FILE *infile = fopen(argv[1], "r"); // 打开第一个参数指定的文件作为输入，文本模式
	FILE *outfile = fopen(argv[2], "wb"); // 打开第二个参数指定的文件作为输出，二进制写模式
	char buf[128]; // 定义128字节的缓冲区来存储文件中的一行
	// 从输入文件中读取每一行，直到文件结束
	while(fgets(buf, 128, infile) != NULL)
	{
		// RISC-V 的基本指令集（RV32I）使用固定长度 32 位的指令编码
		// uint32_t恰好是 32 位（4 字节）的无符号整数
		uint32_t instruction = strtol(buf, NULL, 16); // 将十六进制字符串转换为32位整数
		// printf("原始字符串:		%s", buf);  // 注意：buf已包含换行符
		// printf("十六进制格式:	0x%08x\n", instruction);
		fwrite(&instruction, 1, 4, outfile);  // 将32位整数写入输出文件
	}
	fclose(infile);
	fclose(outfile);
	return 0;
}
