#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"Instr.h"

/// @brief ALU根据输入计算，指令类型计算输出
/// @param inst 指向译码指令结果的指针
/// @param input1 ALU的第一个输入参数
/// @param input2 ALU的第二个输入参数
/// @return ALU计算结果
uint64_t alu_cal(const instr_t *inst, uint64_t input1, uint64_t input2)
{
    // 将两个输入看作有符号数
    int64_t s1 = *(int64_t *)&input1;
    int64_t s2 = *(int64_t *)&input2;
    switch (inst->opcode)
    {
        case 0x03:  // Load         - 加载
        case 0x23:  // Store        - 储存
        case 0x63:  // Branch       - 条件分支
        case 0x6f:  // jal          - 跳转
        case 0x67:  // jalr
        case 0x37:  // lui
        case 0x17:  // auipc
            return input1 + input2;
        case 0x33:  // R-Type
        case 0x13:  // I-Type
            switch(inst->funct3)
            {
                case 0x00:  // add, sub, addi
                    switch(inst->funct7)
                    {
                        case 0x20:
                            return input1 - input2;
                        default: 
                            return input1 + input2;
                    }
                case 0x01:  // sll, slli
                // 只保留input2的低5位（值范围0-31）
                // 因为在32位架构中，移位操作只需要5位就能表示所有有效的移位量（0-31位）
                    input2 = input2 & 0x1f;
                    return input1 << input2;
                case 0x02:  // slt, slti
                    return (s1 < s2) ? 1 : 0;
                case 0x03:  // sltu, sltiu
                    return (input1 < input2) ? 1 : 0;
                case 0x04:  // xor, xori
                    return input1 ^ input2;
                case 0x05:  // srl, sra, srli, srai
                    input2 = input2 & 0x1f;
                    switch(inst->funct7)
                    {
                        case 0x00:  // srl, srli
                            return input1 >> input2;
                        case 0x20:  // sra, srai
                            return s1 >> input2;
                        default: goto UNKNOWN;                            
                    }
                case 0x06:  // or, ori
                    return input1 | input2;
                case 0x07:  // and, andi
                    return input1 & input2;
                default: goto UNKNOWN;
            }
        default: goto UNKNOWN;
    }
UNKNOWN:
    printf("Unknown instruction to ALU.\n");
    exit(0);
}