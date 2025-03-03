#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

// 外部依赖：由其他源文件实现

extern uint8_t *mem;
extern uint64_t va2pa_s(uint64_t vaddr);
extern uint64_t *xreg;
extern uint64_t pcnt;

/// @brief 将二进制文件<file>中的指令数据加载到内存中
/// @param file 二进制文件的路径地址
/// @param text_start 指令在内存中的起始地址(虚拟地址)
/// @param stack_start 程序运行栈的起始地址(虚拟地址)
/// @return 加载到内存中的连续指令字节大小
int load_image(const char *file, uint64_t text_start, uint64_t stack_start)
{
    // 打开二进制文件
    FILE *image = fopen(file, "rb");
    if(image == NULL)
    {
        printf("Connot open file: '%s'\n", file);
        exit(1);
    }
    // 按照4字节一次， 读取二进制文件中的指令数据
    uint32_t buf, text_size = 0, s = 0;
    while(1)
    {
        // 从image文件中读取一个32位无符号整数（4字节），存储到变量buf中，并将实际读取成功的项数赋值给s
        // 1: 要读取的数据项数量，这里是1个
        s = fread(&buf, sizeof(uint32_t), 1, image);
        if(s == 1)
        {
            // 成功读取到4字节数据
            uint64_t vaddr = text_start + text_size;
            *(uint32_t *)&mem[va2pa_s(vaddr)] = buf;
            text_size += sizeof(uint32_t);
        }
        else break;
    }

    // 程序计数器PC设置为<text_start>
    // 栈指针x2(sp)设置为<stack_start>
    pcnt = text_start;
    xreg[2] = stack_start;
    fclose(image);
    return text_size;
}