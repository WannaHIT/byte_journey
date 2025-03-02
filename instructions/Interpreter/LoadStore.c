#include<stdint.h>

// va2pa的函数指针类型， 用于函数指针参数传递
typedef uint64_t (*va2pa_t)(uint64_t);

/// @brief 将数据写入内存的有效地址
/// @param val 待写入内存的数据
/// @param vaddr 内存的有效地址(虚拟地址)
/// @param funct3 用于确定写入数据的宽度，b，h，w
/// @param mem 指向译物理内存的指针
/// @param va2pa_store 指向译va2pa_store的函数指针
void store_data(uint64_t val, uint64_t vaddr, uint32_t funct3,
                uint8_t *mem, va2pa_t va2pa_store)
{
    // MMU 将虚拟地址翻译为物理地址
    uint64_t paddr = va2pa_store(vaddr);
    // 计算数据宽度
    int width = 1 << (funct3 & 3);
    // 以字节数组的形式按顺序写入物理内存
    uint8_t *byte_arr = (uint8_t *)&val;
    for(int i=0; i<width; ++i)
    {
        // Little End
        mem[paddr + i] = byte_arr[i];
    }
}

/// @brief 从内存的有效地址加载数据
/// @param vaddr 内存的有效地址(虚拟地址)
/// @param funct3 用于确定写入数据的宽度，b，h，
/// @param mem 指向译物理内存的指针
/// @param va2pa_laod 用于Load的va2pa地址翻译函数
/// @return 内存中所加载数据， 待写入LMD寄存器
uint64_t load_data(uint64_t vaddr, uint32_t funct3, const uint8_t *mem, 
                    va2pa_t va2pa_load)
{
    // MMU 将虚拟地址翻译为物理地址 
    uint64_t paddr = va2pa_load(vaddr);
    // 计算数据宽度
    int width = 1 << (funct3 & 3);
    // 判断是否加载为无符号数，用于符号位扩展
    int udata = (funct3 >> 2) & 1;
    // 以字节数组的形式按顺序加载物理内存
    uint8_t buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    for(int i=0; i<width; ++i)
    {
        // Little End
        buffer[i] = mem[paddr + i];
    }
    // 符号扩展为LMD的宽度
    if(udata==0 && (buffer[width-1] & 0x80)==0x80)

    {
        for(int i=width; i<8; ++i)
        {
            buffer[i] =0xff;
        }
    }
    return *(uint64_t *)&buffer;
}
