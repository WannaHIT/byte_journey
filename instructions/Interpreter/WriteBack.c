#include<stdint.h>
#include"Instr.h"

/// @brief 更新程序计数器PC, 顺序执行或分支跳转
/// @param inst 指向译码结果结构体instr_t的指针
/// @param reg 指向寄存器数组的指针
/// @param alu_output ALU的计算结果
/// @param lmd 内存中取到的数据
/// @param nextpc next pc : pc + 4
void write_back(const instr_t *inst, uint64_t *reg,
                const uint64_t alu_output, const uint64_t lmd, const uint64_t nextpc)
{
    if(inst->rd == 0)
        // x0寄存器hard-wired， 恒为0
        // 因此不向x0寄存器写入任何数据
        return;
    switch(inst->opcode)
    {
        case 0x33:  // R: op        rd, rs1, rs2
        case 0x13:  // I: op        rd, rs1, imm
        case 0x17:  // U: auipc     rd, imm
        case 0x37:  // U: lui       rd, imm
            reg[inst->rd] = alu_output;
            break;
        case 0x6f:  // J: jal       rd, imm
        case 0x67:  // I: jalr      rd, offset(rs1)
            reg[inst->rd] = nextpc;
            break;
        case 0x03: // Load指令，写回LMD
            reg[inst->rd] = lmd;
            break;
        default:
            break;
    }
}