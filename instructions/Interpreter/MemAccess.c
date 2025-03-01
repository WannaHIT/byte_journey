#include<stdint.h>
#include"Instr.h"
// 外部依赖：由其他源文件实现 
typedef uint64_t (*va2pa_t)(uint64_t);
extern uint64_t load_data(uint64_t vaddr, uint32_t funct3,
                        const uint8_t *mem, va2pa_t va2pa_load);
extern void store_data(uint64_t val, uint64_t vaddr, uint32_t funct3,
                        uint8_t *mem, va2pa_t va2pa_store);
extern uint64_t update_pc(const instr_t *inst, uint64_t npc, uint64_t target,
                        uint64_t condition);

/// @brief 访存： Load/Store 架构
/// @param inst 指向译码结果结构体instr_t的指针
/// @param alu_output EX阶段，ALU的计算结果
/// @param condition EX阶段，条件分支的计算结果
/// @param npc IF阶段，NPC的计算结果
/// @param mem 指向译物理内存的指针
/// @param va2pa_laod 指向译va2pa_laod的函数指针
/// @param va2pa_store 指向译va2pa_store的函数指针
/// @param lmd 指向Load Memory Data寄存器的指针
/// @return 下一条指令的虚拟地址
uint64_t memory_access(const instr_t *inst, uint64_t alu_output, int condition,
    uint64_t npc, uint8_t *mem, va2pa_t va2pa_load, va2pa_t va2pa_store, 
    uint64_t *lmd)
{
    switch(inst->opcode)
    {
        case 0x03:
            *lmd = load_data(alu_output, inst->funct3, mem, va2pa_load);
            break;
        case 0x23:
            store_data(inst->rs2_val, alu_output, inst->funct3, mem, va2pa_store);
            break;
        default: break;
    }
    // 更新程序计数器PC，选择NPC或ALU的计算结果
    return update_pc(inst, npc, alu_output, condition);
}