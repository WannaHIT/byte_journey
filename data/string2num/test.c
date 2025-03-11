#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	long a = strtol(argv[1], NULL, 16);
	printf("The result %ld\n", a);
	return 0;
}
