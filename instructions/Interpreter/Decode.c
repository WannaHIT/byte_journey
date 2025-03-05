#include<stdint.h>
#include"Instr.h"

extern void color_print(instr_t *inst);
/// @brief 译码：将IR寄存器的指令数据翻译为对应的字段
/// @param ir IR寄存器的数值(指令数据)
/// @param reg 指向寄存器数组的指针
/// @param inst 指向译码结果结构体instr_t的指针
void instruction_decode(const uint64_t ir, const uint64_t *reg, instr_t *inst)
{
    // 固定字段
    inst->opcode    = ir            & 0x7f;
    inst->rd        = (ir >> 7)     & 0x1f;
    inst->funct3    = (ir >> 12)    & 0x7;
    inst->funct7    = (ir >> 25)    & 0x7f;
    //
    inst->rs1 = (ir >> 15) & 0x1f;
    inst->rs2 = (ir >> 20) & 0x1f;
    // 读取源寄存器RS1，RS2的数值
    inst->rs1_val   = reg[inst->rs1];
    inst->rs2_val   = reg[inst->rs2];
    // 译码立即数， 并符号扩展到32位有符号数<int32_t>
    int32_t signed_ir = *(int32_t *)&ir;
    switch (inst->opcode)
    {
        case 0x03:  // Load指令 -I
        case 0x13:  // 立即数算术逻辑运算 -I
        case 0x67:  // jalr 跳转 -I
            inst->imm =     signed_ir >> 20;
            break;
        case 0x23:  // Store指令 -S
            inst->imm =     (signed_ir >> 20)   & 0xffffffe0;
            inst->imm |=     (signed_ir >>  7)  & 0x0000001f;
            break;
        case 0x63:  // 条件分支-B
        // 该立即数在原始指令中是分散存储的
            // inst->imm =     (signed_ir >> 19)   & 0xfffff000; // 12
            // inst->imm |=     (signed_ir <<  4)  & 0x00000800; // 11
            // inst->imm |=     (signed_ir >>  20)  & 0xffffffe0; // [5:10]
            // inst->imm |=     (signed_ir >>  7)  & 0x0000001e; // [4:1]
             // 条件分支-B
            // 该立即数在原始指令中是分散存储的
            inst->imm = (signed_ir >> 19) & 0xfffff000; // 12 (符号扩展)B型指令中立即数代表偏移量，可正可负
            inst->imm |= (signed_ir << 4) & 0x00000800; // 11
            inst->imm |= (signed_ir >> 20) & 0x000007e0; // [10:5]
            inst->imm |= (signed_ir >> 7) & 0x0000001e; // [4:1]
            break;
            // break;
        case 0x37:  // lui -U
        case 0x17:  // auipc -U
            inst->imm = signed_ir & 0xfffff000;
            break;
        case 0x6f:  // jal -J
            inst->imm =     (signed_ir >> 11)   & 0xfff00000;
            inst->imm |=     signed_ir          & 0x000ff000;
            inst->imm |=     (signed_ir >>  9)  & 0x00000800;
            inst->imm |=     (signed_ir >>  20) & 0x000007fe;
            break;
        default:
            inst->imm = 0;
            break;
    }
    color_print(inst);
}