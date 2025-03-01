#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int a, b;
	a = strtol(argv[1], NULL, 10);
	b = strtol(argv[2], NULL, 10);
	printf("add is %d\n", a+b);
	return 0;
}
