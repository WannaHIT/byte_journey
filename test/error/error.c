#include <stdio.h>
#include <stdint.h>

void func1()
{
    // 模拟 PC=0x40 和 offset=-52 (0xFFFFFFCC)
    uint64_t pc = 0x40;
    int32_t imm = -52;  // B型指令的立即数偏移量
    printf("\n方法1 (错误): uint64_t target = pc + (uint64_t)imm;\n");
    printf("PC = 0x%lx\n", pc);
    printf("Immediate (32-bit signed) = %d (0x%x)\n", imm, imm);

    // 四个方法没有独立，后面的方法可能用的是类型转换的值
    // 方法1：错误的方式 - 直接将32位立即数视为无符号64位
    uint64_t target1 = pc + (uint64_t)imm;
    
    printf("pc = %lx\n", pc);
    printf("(uint64_t)imm = %lx\n", (uint64_t)imm);
    printf("结果: 0x%lx\n", target1);
    printf("问题: 将有符号32位值直接转为无符号64位会丢失符号信息\n");
}
void func2()
{
    // 模拟 PC=0x40 和 offset=-52 (0xFFFFFFCC)
    uint64_t pc = 0x40;
    int32_t imm = -52;  // B型指令的立即数偏移量
    // 方法2：通过指针转换的方式（可能问题）
    
    int64_t signed_imm = (int64_t)imm;
    uint64_t target2 = pc + *(uint64_t*)&signed_imm;
    printf("\n方法2 (可能问题): int64_t signed_imm = imm; target = pc + *(uint64_t*)&signed_imm;\n");
    printf("pc = %lx\n", pc);
    printf("*(uint64_t*)&signed_imm = %lx\n", *(uint64_t*)&signed_imm);
    printf("结果: 0x%lx\n", target2);
    printf("问题: 通过指针转换可能会导致未定义行为\n");
}

void func3()
{
    // 模拟 PC=0x40 和 offset=-52 (0xFFFFFFCC)
    uint64_t pc = 0x40;
    int32_t imm = -52;  // B型指令的立即数偏移量
    // 方法3：正确的方式 - 使用有符号整数扩展
    int64_t offset = imm;  // 正确的符号扩展
    uint64_t target3 = pc + offset;
    printf("\n方法3 (正确): int64_t offset = imm; target = pc + offset;\n");
    printf("pc = %lx\n", pc);
    printf("imm_int64_t = %lx\n", offset);
    
    printf("结果: 0x%lx\n", target3);
    printf("这是正确答案: 0x40 + (-52) = 0x%lx\n", (uint64_t)0xc);
}

void func4()
{
    // 模拟 PC=0x40 和 offset=-52 (0xFFFFFFCC)
    uint64_t pc = 0x40;
    int32_t imm = -52;  // B型指令的立即数偏移量
    // 方法4：显式强制转换链（你的解决方案）
    int32_t raw_offset = (int32_t)(uint32_t)imm; //ffffffcc
    int64_t signed_offset = (int64_t)raw_offset;
    uint64_t target4 = pc + signed_offset;
    printf("\n方法4 (你的解决方案): 通过显式类型转换链\n");
    printf("pc = %lx\n", pc);
    printf("raw_offset = %x\n", raw_offset);    //ffffffcc
    printf("signed_offset = %lx\n", signed_offset);
    
    printf("结果: 0x%lx\n", target4);
}
// 模拟分支指令计算目标地址的不同方法
int main() {
    
    
    func1();
    func2();
    func3();
    func4();
    
    return 0;
}
