#include<stdio.h>
#include<stdlib.h>
#include<inttypes.h>

// ANSI 颜色代码
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

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
	// 类型重解释（type punning）技术，使得同一块内存可以被不同类型解释
	int32_t *xp = (int32_t *)&x;
	int32_t *yp = (int32_t *)&y;

	// 检查无符号数是否溢出
	if(uint32_overflow(x, y) == 1)
		// PRIu32 是一个格式说明符宏, 正确打印 uint32_t 类型的无符号整数值
		printf(GREEN"unsigned: %"PRIu32" Overflow\n" RESET, x+y);
	else 
		printf(RED"unsigned: %"PRIu32" No overflow\n" RESET, x+y);
	// 检查无符号数是否溢出
	if(int32_overflow(*xp, *yp) == 1)
		printf(GREEN "Signed: %"PRId32" Overflow\n\n" RESET, *xp + *yp);
	else 
		printf(GREEN "Signed: %"PRId32" No overflow\n\n" RESET, *xp + *yp);
	return 0;
}
