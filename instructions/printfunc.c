#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
/// @brief 打印函数指令的函数
/// @param func 待打印函数的函数指针
void print_func(void *func)
{
	uint32_t a = *(uint32_t *)func;
	uint8_t *b = (uint8_t *)&a;

	// 直到遇到ret指令为止
	// 仅限于函数以ret返回的情况
	while(1)
	{
		printf("%p: %02x %02x %02x %02x\n", func, b[0], b[1], b[2], b[3]);
		if(a == 0x00008067) break;
		// 更新函数指针的位置：下一条指令
		func += 4;
		a = *(uint32_t *)func;
		b = (uint8_t *)&a;
	}
}

/* main function */
void main()
{
	// 打印main自身
	print_func(&main);
}
