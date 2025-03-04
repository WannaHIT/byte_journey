#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int a, b;
	int c;

	a = strtol(argv[1], NULL, 10);
	b = strtol(argv[2], NULL, 10);

	c = a + b;
	printf("add is %d\n", c);
	return 0;
}
