#include <stdio.h>
#include <stdint.h>

// 定义指令结构体
typedef struct INSTR_STRUCT
{
    uint32_t opcode;    // 操作码
    uint32_t funct3;    // func3 (如果不存在，则为0)
    uint32_t funct7;    // func7 (如果不存在，则为0)
    uint32_t rd;        // 目标寄存器RD的编号
    uint64_t rs1_val;   // 源寄存器RS1的数值
    uint64_t rs2_val;   // 源寄存器RS2的数值
    uint32_t imm;       // 32位符号扩展的立即数
} instr_t;

// 辅助函数：打印 32 位数值的二进制格式
void print_binary_32(uint32_t value) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (value >> i) & 1);
        if (i % 4 == 0) printf(" ");  // 每 4 位加一个空格
    }
}

// 辅助函数：打印 64 位数值的二进制格式
void print_binary_64(uint64_t value) {
    for (int i = 63; i >= 0; i--) {
        printf("%ld", (value >> i) & 1);
        if (i % 4 == 0) printf(" ");  // 每 4 位加一个空格
    }
}

// 打印指令结构体
void print_instr(instr_t inst) {
    printf("Opcode:  "); print_binary_32(inst.opcode); printf(" (0x%X)\n", inst.opcode);
    printf("Funct3:  "); print_binary_32(inst.funct3); printf(" (0x%X)\n", inst.funct3);
    printf("Funct7:  "); print_binary_32(inst.funct7); printf(" (0x%X)\n", inst.funct7);
    printf("RD:      "); print_binary_32(inst.rd); printf(" (0x%X)\n", inst.rd);
    printf("RS1 Val: "); print_binary_64(inst.rs1_val); printf(" (0x%lX)\n", inst.rs1_val);
    printf("RS2 Val: "); print_binary_64(inst.rs2_val); printf(" (0x%lX)\n", inst.rs2_val);
    printf("IMM:     "); print_binary_32(inst.imm); printf(" (0x%X)\n", inst.imm);
}

int main() {
    instr_t test_instr = {
        .opcode = 0b0000000000000000000000000110011,
        .funct3 = 0b000,
        .funct7 = 0b0000000,
        .rd = 0b1010,
        .rs1_val = 0x123456789ABCDEF0,
        .rs2_val = 0x0FEDCBA987654321,
        .imm = 0b00000000000000000000010100000000
    };

    print_instr(test_instr);

    return 0;
}

