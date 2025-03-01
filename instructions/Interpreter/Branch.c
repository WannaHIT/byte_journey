#include<stdint.h>
#include<stdlib.h>
#include"Instr.h"

/// @brief 根据寄存器的数值计算条件分支
/// @param inst  inst指向instr_t的指针
/// @return 条件成立，返回1；否则，返回0
uint64_t branch_cal(const instr_t *inst)
{
    uint64_t u1 = inst->rs1_val;
    uint64_t u2 = inst->rs2_val;
    int64_t s1 = *(int64_t *)&u1;
    int64_t s2 = *(int64_t *)&u2;
    switch (inst->funct3)
    {
        case 0x0: return s1 == s2;  // beq
        case 0x1: return s1 != s2;  // bne
        case 0x4: return s1 <  s2;  // blt
        case 0x5: return s1 >= s2;  // bge  
        case 0x6: return u1 <  u2;  // bltu  
        case 0x7: return u1 >= u2;  // bgeu
        default: exit(1);
    }
}