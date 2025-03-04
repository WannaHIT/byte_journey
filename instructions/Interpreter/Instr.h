#include<stdint.h>
typedef struct INSTR_STRUCT
{                       // 保存指令译码结果的结构体
    uint32_t opcode;    // opcode
    uint32_t funct3;    // func3 (如果不存在，则为0)
    uint32_t funct7;    // func7 (如果不存在，则为0)
    uint32_t rd;        // 目标寄存器RD的<编号>
    uint64_t rs1_val;   // 源寄存器RS1的<数值> // 写成了32位， fuck!!!!
    uint64_t rs2_val;   // 源寄存器RS2的<数值> // 写成了32位， fuck!!!!
    uint32_t imm;       // 32位符号扩展位的立即数
} instr_t;