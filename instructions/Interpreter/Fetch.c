#include<stdint.h>
typedef uint64_t (*va2pa_t)(uint64_t); // 定义一个函数指针类型

/// @brief 取指：根据PC， 将指令数据从内存加载到IR中
/// @param pc 程序计数器PC的值
/// @param mem 内存数组指针
/// @param va2pa_load 虚拟内存映射到物理内存
/// @param npc  NPC指针
/// @return 应当写入IR寄存器的数值(指令数据)
uint32_t instruction_fetch(uint64_t pc, const uint8_t *mem,
    va2pa_t va2pa_load, uint64_t *npc)
{
    // 更新NPC
    *npc = pc + 4;
    // 虚拟地址翻译， 读取指令内存
    return *((uint32_t *)(&mem[va2pa_load(pc)]));
}
