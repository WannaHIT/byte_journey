#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		return 0;
	}
	FILE *infile = fopen(argv[1], "r");
	FILE *outfile = fopen(argv[2], "wb"); 
	char buf[128];
	while(fgets(buf, 128, infile) != NULL)
	{
		uint32_t instruction = strtol(buf, NULL, 16);
		fwrite(&instruction, 1, 4, outfile);
	}
	fclose(infile);
	fclose(outfile);
}
