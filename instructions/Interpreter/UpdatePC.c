#include<stdint.h>
#include"Instr.h"

/// @brief 更新程序计数器PC, 顺序执行或分支跳转
/// @param inst 指向译码结果结构体instr_t的指针
/// @param nextpc next pc: pc + 4
/// @param target ALU计算的目标地址
/// @param condition 条件分支是否成立
/// @return 下一条指令的虚拟地址(pc值)
uint64_t update_pc(const instr_t *inst, uint64_t nextpc, uint64_t target,
    uint64_t condition)
{
    switch(inst->opcode)
    {
        case 0x63:  // 条件分支     -B
            return condition == 1 ? target : nextpc;
        case 0x67:  // jalr     -无条件跳转
        case 0x6f:  // jal     -无条件跳转
            return target;   
        default:
            return nextpc;
    }
}