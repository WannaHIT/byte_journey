#include<stdio.h>
#include<inttypes.h>
// 位的表示不变， 但是解释变了
int8_t add(uint8_t a, uint8_t b)
{
	return a + b;
}
// 无符号和有符号运算==>无符号
// 表示形式还是由 这个函数声明的类型决定的
uint8_t mixadd(int8_t a, uint8_t b)
{
	return a + b;
}

int main(void)
{
	int8_t c = add(64u, 64u);
	printf("c = %d.\n", c);
	int8_t d = add(133u, 122u);
	printf("d = %d.\n", d);

	uint8_t e = mixadd(1, 127u);
	printf("e = %d.\n", e);
	return 0;
}
