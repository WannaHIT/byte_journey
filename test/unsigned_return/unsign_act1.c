#include<stdio.h>
#include<inttypes.h>
// 如果操作数小于 int 的大小（如 uint8_t 和 int8_t），
// 它们会先被提升为 int 类型再进行比较

int main(void)
{
	unsigned int  a = 127;
	int  b = -1;
	printf("a = %u, b = %d\n", a, b); // 打印 a 和 b 的值
    printf("a = %u, (unsigned int )b = %u\n", a, (unsigned int )b); // 打印 a 和 b 转换后的值
	if( a > b )
	{
		printf("unsigned 127 is bigger than int -1.\n");
	}
	else{
		printf("Aha, gotta Ya.\n");
	}
	return 0;
}