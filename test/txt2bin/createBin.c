#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		// printf("Param numbers are not right.\n");
		fprintf(stderr, "Wrong Param numbers.\n");
		exit(1);
	}
	FILE *input = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "wb");
	char buf[128];

	while(fgets(buf, 128, input) != NULL)
	{
		uint32_t intruction = strtol(buf, NULL, 16);
		fwrite(&intruction, 1, 4, output);
	}

	fclose(input);
	fclose(output);
	return 0;
}
