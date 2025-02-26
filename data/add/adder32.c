#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
/// @brief 32位加法器，支持有符号数和无符号数加减法
/// @param x 加法输入比特串，注意 这不是数值！
/// @param y 加法输入比特串，注意 这不是数值！
/// @param cf 进位指针。如果无符号数溢出，设为1
/// @param sf 符号位指针。设为加减法结果的最高符号位
/// @param of 有符号数字溢出指针， 如果溢出，设为1
/// @return 加减法结果的比特串。注意这不是数值！

uint32_t adder_32(uint32_t x, uint32_t y, uint32_t *cf, uint32_t *sf, uint32_t *of)
{
	uint32_t a = 0; // 加法器结果比特串
	uint32_t cj = 0; // cj即c[i+1]，输出的进位
	uint32_t ci = 0; // c[i], 输入的进位，c[0]必定为0
	uint32_t xi = 0; // x的第i位 x[i]
	uint32_t yi = 0; // y的第i位 y[i]
	uint32_t ai = 0; // a的第i位 a[i]
	
	// 从最低位[0]到最高位[31]，按位相加
	for(uint32_t i=0; i<32; ++i)
	{
		xi = ((x>>i) & 1); // x[i]
		yi = ((y>>i) & 1); // y[i]
		ci = cj;		   // c[i], 即上一组的进位结果		
		
		// p25真值表来计算结果，a[i], c[i+1]
		ai = (xi ^ yi ^ ci);
		cj = (xi & yi) | (ci & (xi ^ yi));

		// 将结果a[i]写入a的比特串
		// a = a | ((ai << 1) << i); // ERROR
		a = a | ((ai & 1) << i);
	}
	// 根据指针，将结果写入指针所指向的内存
	*cf = (cj & 1);
	*sf = (ai & 1);
	*of = ((ci ^ cj) & 1);
	return a;
}

/* --------- main : Entry Point ----------*/
int main(int argc, char *argv[])
{
	uint32_t cf, sf, of;
	// 将命令行的参数转换为加法器的输入比特串
	uint32_t x = strtol(argv[1], NULL, 10);
	uint32_t y = strtol(argv[2], NULL, 10);

	// 进行加法器运算
	uint32_t a = adder_32(x, y, &cf, &sf, &of);
	// 打印结果：结果比特串，CF，SF，of
	printf("0x%x + 0x%x = 0x%x\nCF=%u, SF=%u, OF=%u\n",
			x, y, a, cf, sf, of);
	return 0;
}
