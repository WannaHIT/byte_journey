#include<stdio.h>
#include<inttypes.h>
#include<stdint.h>
#include"Instr.h"

// RV32I指令集,6种格式
typedef uint64_t(*va2pa_t)(uint64_t);


/// @breif 打印彩色的指令二进制翻译
/// @param inst 指向指令结构体的指针
void color_print(instr_t *inst)
{
	// printf("Decoded:            opcode=0x%x, rd=%x, rs1=%ld, rs2=%ld, imm=0x%x\n", 
    //    inst.opcode, inst.rd, inst.rs1_val, inst.rs2_val, inst.imm);
	switch(inst->opcode)
	{
		case 0x33: // -R
			printf("\n\n*********************************\n");
			printf("Instrution Type: ---R-type.\n");
			printf("inst->funct7: 					0x%" PRIx32 "\n", inst->funct7); // 使用 PRIu32 宏
			printf("inst->rs2_val: 					0x%" PRIx64 "\n", inst->rs2_val); 
    		printf("inst->rs1_val : 	 			0x%" PRIx64 "\n", inst->rs1_val); // 使用 PRIu64 宏
			
			printf("inst->funct3:					0x%" PRIx32 "\n", inst->funct3); 
			
			printf("inst->rd: 						0x%" PRIx32 "\n", inst->rd); 
			
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			printf("*********************************\n\n");
			// funct7			rs2		rs1		funct3 		rd			opcode
			// [31:25]  		[24:20] [19:15]  [14:12]    [11:7]   	[6:0]

			break;
		case 0x03: // -I
		case 0x67:
		case 0x13:
			// imm[11:0]				rs1		funct3		rd			opcode
			// [31:20]					[19:15]  [14:12]    [11:7]   	[6:0]
			printf("\n\n*********************************\n");
			printf("Instrution Type: ---I-type.\n");
			printf("inst->imm: 						0x%" PRIx32 "\n", inst->imm);
			printf("inst->rs1_val : 	 			0x%" PRIx64 "\n", inst->rs1_val);
			printf("inst->funct3:					0x%" PRIx32 "\n", inst->funct3); 
			printf("inst->rd: 						0x%" PRIx32 "\n", inst->rd); 
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			printf("*********************************\n\n");
			break;
		case 0x23: // -S
			// imm[11:5] 		rs2		rs1		funct3		imm[4:0]	opcode
			// [31:25]			[24:20] [19:15]  [14:12]	[11:7]		[6:0]
			printf("\n\n*********************************\n");
			printf("Instrution Type: ---S-type.\n");
			printf("inst->imm: 						0x%" PRIx32 "\n", inst->imm);
			printf("inst->rs2_val: 					0x%" PRIx64 "\n", inst->rs2_val); 
    		printf("inst->rs1_val : 	 			0x%" PRIx64 "\n", inst->rs1_val);
			printf("inst->funct3:					0x%" PRIx32 "\n", inst->funct3); 
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			printf("*********************************\n\n");
			break;
		case 0x63: // -B
			// i12 imm[10:5]	rs2		rs1		funct3		imm[4:1]i11	opcode
			// 31	[30:25]		[24:20] [19:15]  [14:12]    [11:7]   	[6:0]
			printf("\n\n*********************************\n");
			printf("Instrution Type: ---B-type.\n");
			printf("inst->imm: 						0x%" PRIx32 "\n", inst->imm);
			printf("inst->rs2_val: 					0x%" PRIx64 "\n", inst->rs2_val); 
    		printf("inst->rs1_val : 	 			0x%" PRIx64 "\n", inst->rs1_val);
			printf("inst->funct3:					0x%" PRIx32 "\n", inst->funct3);
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			printf("*********************************\n\n");
			break;
		case 0x37: // -U
		case 0x17:
			// imm[31:12]									rd			opcode
			// [31:12]										[11:7]   	[6:0]
			printf("\n\n*********************************\n");
			printf("Instrution Type: ---U-type.\n");
			printf("inst->imm: 						0x%" PRIx32 "\n", inst->imm);
			printf("inst->rd: 						0x%" PRIx32 "\n", inst->rd); 
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			printf("*********************************\n\n");
			break;
		case 0x6f: // -J
			// i20 imm[10:1]			i11 imm[19:12]		rd			opcode
			// 31, [30:21]				20, [19:12]			[11:7]   	[6:0]
			printf("\n\n*********************************\n");
			printf("Instrution Type: ---J-type.\n");
			printf("inst->imm: 						0x%" PRIx32 "\n", inst->imm);
			printf("inst->rd: 						0x%" PRIx32 "\n", inst->rd); 
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			printf("*********************************\n\n");
			break;
		default:
			break;
	}
}
