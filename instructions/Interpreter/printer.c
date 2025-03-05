#include<stdio.h>
#include<inttypes.h>
#include<stdint.h>
#include"Instr.h"

// RV32I指令集,6种格式,对每条译码的指令重新以二进制打印出来和网站对比
typedef uint64_t(*va2pa_t)(uint64_t);

/// @breif 打印彩色的指令二进制翻译
/// @param inst 指向指令结构体的指针
void color_print(instr_t *inst)
{
	int arr[32] = {0};
	for(int i=0;i<32; ++i) arr[i] = 0; // Init

	switch(inst->opcode)
	{
		case 0x33: // -R
			printf("*********************************\n");
			printf("Instrution Type: ---R-type.\n");
			printf("inst->funct7: 					0x%" PRIx32 "\n", inst->funct7); // 使用 PRIu32 宏
			// 我知道了，rs2_val和rs2不一样！！！！！！！！
			// rs2 = inst->rs1_val
			printf("inst->rs2: 					0x%" PRIx8 "\n", inst->rs2); 
    		printf("inst->rs1 : 	 				0x%" PRIx8 "\n", inst->rs1); // 使用 PRIu64 宏			
			printf("inst->funct3:					0x%" PRIx32 "\n", inst->funct3); 			
			printf("inst->rd:					0x%" PRIx32 "\n", inst->rd); 			
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			// funct7			rs2		rs1		funct3 		rd			opcode
			// [31:25]  		[24:20] [19:15]  [14:12]    [11:7]   	[6:0]
			for(int i=0; i<32; i++)
			{
				if(i>=0 && i <=6)
					arr[i] = (inst->opcode >> i) & 0x1;
					// opcode = opcode >> 1;
				else if (i >= 7 && i <= 11)
					arr[i] = (inst->rd >> (i-7)) & 0x1;
				else if(i >= 12 && i <= 14)
					arr[i] = (inst->funct3 >> (i-12)) & 0x1;
				else if(i >= 15 && i <= 19)
					arr[i] = (inst->rs1 >> (i-15)) & 0x1;
				else if(i >= 20 && i <= 24)
					arr[i] = (inst->rs2 >>(i-20)) & 0x1;
				else if(i >= 25 && i <= 31)
					arr[i] = (inst->funct7 >> (i-25)) & 0x1;
			}
			break;
		case 0x03: // -I
		case 0x67:
		case 0x13:
			// imm[11:0]				rs1		funct3		rd			opcode
			// [31:20]					[19:15]  [14:12]    [11:7]   	[6:0]
			printf("*********************************\n");
			printf("Instrution Type: ---I-type.\n");
			printf("inst->imm: 						0x%" PRIx32 "\n", inst->imm);
			printf("inst->rs1_val : 	 			0x%" PRIx8 "\n", inst->rs1);
			printf("inst->funct3:					0x%" PRIx32 "\n", inst->funct3); 
			printf("inst->rd: 						0x%" PRIx32 "\n", inst->rd); 
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			
			for(int i=0;i<32;i++)
			{
				if(i >=0 && i <=6)
					arr[i] = (inst->opcode >> i) & 0x1;
				else if (i >= 7 && i <= 11)
					arr[i] = (inst->rd >> (i-7)) & 0x1;
				else if(i >= 12 && i <= 14)
					arr[i] = (inst->funct3 >> (i-12)) & 0x1;
				else if(i >= 15 && i <= 19)
					arr[i] = (inst->rs1 >> (i-15)) & 0x1;
				else 
					arr[i] = (inst->imm >> (i-20)) & 0x1;
			}
			break;
		case 0x23: // -S
			// imm[11:5] 		rs2		rs1		funct3		imm[4:0]	opcode
			// [31:25]			[24:20] [19:15]  [14:12]	[11:7]		[6:0]
			printf("*********************************\n");
			printf("Instrution Type: ---S-type.\n");
			printf("inst->imm: 						0x%" PRIx32 "\n", inst->imm);
			printf("inst->rs2_val: 					0x%" PRIx8 "\n", inst->rs2); 
    		printf("inst->rs1_val : 	 			0x%" PRIx8 "\n", inst->rs1);
			printf("inst->funct3:					0x%" PRIx32 "\n", inst->funct3); 
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			// 先截取低5位
			uint32_t lowbit = inst->imm & 0x1f;
			// 再截取高7位
			uint32_t highbit = inst->imm & 0xfe0;
			for(int i=0;i<32;i++)
			{
				if(i >=0 && i <=6)
					arr[i] = (inst->opcode >> i) & 0x1;
				else if( i>= 7 && i <=11)									
					arr[i] = (lowbit >> (i-7)) & 0x1;				
				else if(i >= 12 && i <= 14)
					arr[i] = (inst->funct3 >> (i-12)) & 0x1;
				else if(i >= 15 && i <= 19)
					arr[i] = (inst->rs1 >> (i-15)) & 0x1;
				else if(i >= 20 && i <= 24)
					arr[i] = (inst->rs2 >>(i-20)) & 0x1;
				else if(i >= 25 && i <= 31)				
					arr[i] = (highbit  >> (i-25)) & 0x1;				
			}
			break;
		case 0x63: // -B
			// i12 imm[10:5]	rs2		rs1		funct3		imm[4:1]i11	opcode
			// 31	[30:25]		[24:20] [19:15]  [14:12]    [11:8]7   	[6:0]
			printf("*********************************\n");
			printf("Instrution Type: ---B-type.\n");
			printf("inst->imm: 						0x%" PRIx32 "\n", inst->imm);
			printf("inst->rs2: 						0x%" PRIx8 "\n", inst->rs2); 
    		printf("inst->rs1: 	 					0x%" PRIx8 "\n", inst->rs1);
			printf("inst->funct3:					0x%" PRIx32 "\n", inst->funct3);
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			uint32_t i11 = inst->imm & 0x800;
			uint32_t i1_4 = inst->imm & 0x1e;
			uint32_t i5_10 = inst->imm & 0x7e0;
			uint32_t i12 = inst->imm & 0x1000;
			for(int i=0;i<32;i++)
			{
				if(i >=0 && i <=6)
					arr[i] = (inst->opcode >> i) & 0x1;
				else if(i==7)				
					arr[i] = i11 & 0x1;				
				else if(i >= 8 && i <= 11)				
					arr[i] = ( i1_4 >> (i-8)) & 0x1;				
				else if(i >= 12 && i <= 14)
					arr[i] = (inst->funct3 >> (i-12)) & 0x1;
				else if(i >= 15 && i <= 19)
					arr[i] = (inst->rs1 >> (i-15)) & 0x1;
				else if(i >= 20 && i <= 24)
					arr[i] = (inst->rs2 >>(i-20)) & 0x1;
				else if(i >= 25 && i <= 30)
					arr[i] = (i5_10 >> (i-25)) & 0x1;
				else 
					arr[i] = (i12 >> (i-31)) & 0x1;
			}
			break;
		case 0x37: // -U
		case 0x17:
			// imm[31:12]									rd			opcode
			// [31:12]										[11:7]   	[6:0]
			printf("*********************************\n");
			printf("Instrution Type: ---U-type.\n");
			printf("inst->imm: 						0x%" PRIx32 "\n", inst->imm);
			printf("inst->rd: 						0x%" PRIx32 "\n", inst->rd); 
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			uint32_t imm = inst->imm & 0xfffff000;
			for(int i=0;i<32;i++)
			{
				if(i >=0 && i <=6)
					arr[i] = (inst->opcode >> i) & 0x1;
				else if(i >=7 && i <=11)
					arr[i] = (inst->rd >> (i-7)) & 0x1;
				else
					arr[i] = (imm >> (i-0)) & 0x1; // 没有位差，所以没有移动
			}
			break;
		case 0x6f: // -J
			// i20 imm[10:1]			i11 imm[19:12]		rd			opcode
			// 31, [30:21]				20, [19:12]			[11:7]   	[6:0]
			printf("*********************************\n");
			printf("Instrution Type: ---J-type.\n");
			printf("inst->imm: 						0x%" PRIx32 "\n", inst->imm);
			printf("inst->rd: 						0x%" PRIx32 "\n", inst->rd); 
			printf("inst->opcode: 					0x%" PRIx32 "\n", inst->opcode);
			uint32_t i12_19 = inst->imm & 0xff000;
			i11 = inst->imm & 0x800;
			uint32_t i1_10 = inst->imm & 0xefe;
			uint32_t i20 = inst->imm & 0x100000;
			for(int i=0;i<32;i++)
			{
				if(i >=0 && i <=6)
					arr[i] = (inst->opcode >> i) & 0x1;
				else if(i >=7 && i <=11)
					arr[i] = (inst->rd >> (i-7)) & 0x1;
				else if(i >=12 && i <=19)
					arr[i] = (i12_19 >> (i-12)) & 0x1;
				else if(i == 20)
					arr[i] = i11 & 0x1;
				else if(i >=21 && i <=30)
					arr[i] = (i1_10 >> (i-21)) & 0x1;
				else 
					arr[i] = i20 & 0x1;
			}
			break;
		default:
			break;
	}
	for(int i=31; i>=0;i --)
	{
		printf("%d", arr[i]);
		if(i % 4 == 0) printf(" ");
	}
		
	printf("\n");
}
