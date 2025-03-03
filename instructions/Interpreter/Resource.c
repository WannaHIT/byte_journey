#include<stdio.h>
#include<stdint.h>
#include<inttypes.h>
// 物理内存：它的大小，以及定义
#define MEM_SIZE (65536)
/* static变量不可以被其他源文件访问*/
static uint8_t mem_static[MEM_SIZE];

// 通用寄存器 x0 - x31
static uint64_t xreg_static[32];

/* 以下变量暴露给其他源文件 */
const uint64_t MEMORY_SIZE = MEM_SIZE;
// 程序计数器
uint64_t pcnt;
// 内存,寄存器数组都以指针形式被访问
uint8_t *mem = mem_static;  // 通过指针的方式，其他源文件仍然可以间接访问这个变量
uint64_t *xreg = xreg_static;
/// @brief 打印所有通用寄存器的值
void dump_registers()
{
    for(int i=0; i<32; ++i)
    {
        // PRIX64 是一个宏，定义在 <inttypes.h> 中，用于格式化输出 64 位无符号整数的十六进制表示
        // PRIu64 是一个宏，定义在 <inttypes.h> 中，用于格式化输出 64 位无符号整数的十进制表示
        // 2 16 22 --- 输出宽度
        printf("X[%2d] %016"PRIX64" %22"PRIu64"\n", i, xreg[i], xreg[i]);
    }
}