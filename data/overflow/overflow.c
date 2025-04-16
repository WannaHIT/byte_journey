#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>

/// @brief 检查32位无符号加法是否溢出
/// @param x 32bits unsigned int 
/// @param y 32bits unsigned int 
/// @return 1 overflow, else 0
int uint32_overflow(uint32_t x, uint32_t y)
{
	return (x + y) < x;
}


/// @brief 检查32位有符号加法是否溢出
/// @param x 32bits signed int 
/// @param y 32bits signed int 
/// @return 1 overflow, else 0
int int32_overflow(int32_t x, int32_t y)
{
	return (x>=0 && y>=0 && (x+y)<0) || 
		(x<0 && y<0 && (x+y>=0));
}

/// @brief main function 主程序
/// @param argc: 命令行参数个数
/// @param argv：命令行字符串的参数
/// @reutrn 主程序退出状态
int main(int argc, char *argv[])
{
	// 以16进制读取4个字节，作为内存上存储的字符串
	// 默认无符号数
	uint32_t x = strtol(argv[1], NULL, 16);
	uint32_t y = strtol(argv[2], NULL, 16);

	// 将x，y的比特串解释为有符号数
	int32_t *xp = (int32_t *)&x;
	int32_t *yp = (int32_t *)&y;

	// 检查无符号数是否溢出
	if(uint32_overflow(x, y) == 1)
		printf("unsigned: %"PRIu32" Overflow\n", x+y);
	else 
		printf("unsigned: %"PRIu32" No overflow\n", x+y);
	// 检查无符号数是否溢出
	if(int32_overflow(*xp, *yp) == 1)
		printf("Signed: %"PRId32" Overflow\n", *xp + *yp);
	else 
		printf("Signed: %"PRId32" No overflow\n", *xp + *yp);
	return 0;
}
