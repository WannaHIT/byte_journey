#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>
#include"Instr.h"

// 虚拟地址翻译的函数指针类型
typedef uint64_t (*va2pa_t)(uint64_t); // 定义一个函数指针类型

// 外部依赖：由其他源文件实现
extern const uint64_t MEMORY_SIZE;
extern uint64_t pcnt;
extern uint8_t *mem;
extern uint64_t *xreg;
extern uint64_t va2pa_l(uint64_t vaddr);
extern uint64_t va2pa_s(uint64_t vaddr);
extern void dump_registers();

/* -------- 模拟取指 -------- */
// 输入：程序计数器PC
// 输出：NPC(引用)， 指令寄存器IR的(返回值)
extern uint32_t instruction_fetch(uint64_t pc, const uint8_t *mem,
    va2pa_t va2pa_load, uint64_t *npc);

/* -------- 模拟译码 -------- */
// 输入：指令寄存器IR的值
// 输出：译码结果：类型，寄存器值，立即数等
extern void instruction_decode(const uint64_t ir, const uint64_t *reg,
    instr_t *condition);

/* -------- 模拟执行 -------- */
// 输入：源寄存器的值，NPC
// 输出：ALU结果(返回值)，分支判断结果(引用)
extern uint64_t instruction_execute(const instr_t *inst, uint64_t npc,
    uint64_t *condition);

/* -------- 模拟访存 -------- */
// 输入：ALU结果(内存有效地址)，源寄存器的值(Store引入内存)，分支判断结果，NPC
// 输出：LMD值(引用)，PC更新值(返回值)
extern uint64_t memory_access(const instr_t *inst, uint64_t alu_output,
    uint64_t condition, uint64_t npc, uint8_t *mem, va2pa_t va2pa_load,
    va2pa_t va2pa_store, uint64_t *lmd);

/* -------- 模拟写回 -------- */
// 输入：ALU结果(计算结果)，LMD值(load内存)
extern void write_back(const instr_t *inst, uint64_t *reg,
    const uint64_t alu_output, const uint64_t lmd, const uint64_t nextpc);

// 从二进制文件中加载指令数据到内存中
extern int load_image(const char *file, uint64_t text_start, 
    uint64_t stack_start);


/* -------- 程序入口 - Entry Point -------- */
int main(int argc, char *argv[])
{
    // 将程序文件中的指令数据加载到内存mem中， 从text_start开始
    uint64_t text_start = strtoull(argv[2], NULL, 16);
    uint64_t stack_start = strtoull(argv[3], NULL, 16);
    printf("Loading image: start_code: %"PRIx64"; stack_start %"PRIX64"\n",
        text_start, stack_start);

    int text_size = load_image(argv[1], text_start, stack_start);
    // Data Path 中不同阶段之间的参数传递
    instr_t inst;                       // decode结果
    uint64_t ir, npc, alu, cond, lmd;   // 临时寄存器
    // 执行指令的主循环
    while(text_start <= pcnt && pcnt < text_start+text_size)
    {
        // 指令数据寄存器IR
        ir = instruction_fetch(pcnt, mem, va2pa_l, &npc);
        printf("PC:                 0x%lx\nIR:                 0x%lx\n", pcnt, ir);

        // 解析指令数据
        instruction_decode(ir, xreg, &inst);
        // color_print函数可以放这里
        // printf("Decoded:            opcode=0x%x, rd=%x, rs1=%ld, rs2=%ld, imm=0x%x\n", 
    //    inst.opcode, inst.rd, inst.rs1_val, inst.rs2_val, inst.imm);

        // ALU运算结果
        alu = instruction_execute(&inst, npc, &cond);
        printf("Execute:            alu=0x%lx\n", alu);

        // 更新程序计数器PC  alu对应target
        pcnt = memory_access(&inst, alu, cond, npc, mem, va2pa_l, va2pa_s, &lmd);
        // 写回目标寄存器
        write_back(&inst, xreg, alu, lmd, npc);
        printf("After writeback:    x1=0x%lx, x12=0x%lx\n\n", xreg[1], xreg[12]);

    }
    printf("Loop exited. Final PC: 0x%lx, text_size: %d\n", pcnt, text_size);
    printf("Final values: x1=0x%lx, x12=0x%lx\n", xreg[1], xreg[12]);
    dump_registers();
    return 0;
}