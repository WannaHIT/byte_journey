#include<stdio.h>
#include<stdlib.h>
#include"Instr.h"

// 外部依赖：由其他源文件实现
extern uint64_t alu_cal(const instr_t *inst, uint64_t input1, uint64_t input2);
extern uint64_t branch_cal(const instr_t *inst);

/// @brief MUX - 多路选择器：选择ALU的两个输入
/// @param inst  指向译码结果结构体instr_t的指针
/// @param npc NPC的数值
/// @param input1 MUX选择的结果：RS1的数值，NPC
/// @param input2  MUX选择的结果：RS2的数值，IMM
static void select_inputs(const instr_t *inst, uint64_t npc, 
    uint64_t *input1, uint64_t *input2)
{
    // 立即数， 并符号扩展到64位有符号数<int64_t>, 方便作为ALU的输入
    int64_t simm = (int64_t)(inst->imm);
    switch (inst->opcode)
    {
        case 0x33:  // R:       rs1, rs2
            *input1 = inst->rs1_val;
            *input2 = inst->rs2_val;
            break;
        case 0x03:  // Load:    rs1, imm
        case 0x13:  // I:       rs1, imm
        case 0x23:  // S:       rs1, imm
        case 0x67:  // jalr:    rs1, offset
            *input1 = inst->rs1_val;
            *input2 = *(uint64_t *)(&simm);
            break;
        case 0x63:  // B:       npc, imm  // npc = npc + imm 
        case 0x17:  // U:       npc, imm(auipc)
        case 0x6f:  // J:       npc, imm
            // 获取当前正在执行的指令的实际地址
            // 当无符号类型和有符号类型进行运算时，有符号类型将被转换为无符号类型，然后进行运算
            // input1 是无符号类型，无符号类型和有符号类型运算得到无符号类型
            *input1 = npc - 4;
            *input2 = *(uint64_t *)(&simm); 
            // *input2 = simm; // 2025   这里也对，位的表示没有变化
            break; ///////////////////BREAK!!!!!!!!!!!!这里导致*input1 = 0;即PC = 0
        case 0x37:  // U:       ---, imm(lui)
            *input1 = 0;
            *input2 = *(uint64_t *)(&simm);
            break;
        default:
            break;
    }
}

/// @brief 执行： 完成ALU， 条件分支的计算
/// @param inst 指向译码指令的指针
/// @param npc NPC的数值
/// @param condition 指向条件分支结果的指针
/// @return ALU计算结果
uint64_t instruction_execute(const instr_t *inst, uint64_t npc, 
    uint64_t *condition)
    {
        // 存放MUX选择的结果， 亦即ALU输入的临时寄存器
        uint64_t input1, input2;
        select_inputs(inst ,npc, &input1, &input2);

        // ALU根据Opcode， Func3/7计算
        uint64_t output = alu_cal(inst ,input1, input2);

        // 根据Opcode， Func3/7计算条件分支是否成立
        *condition = 0;
        if(inst->opcode == 0x63)
            *condition = branch_cal(inst);
        return output;
    }