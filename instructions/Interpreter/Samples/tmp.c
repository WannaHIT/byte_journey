#include<stdio.h>

extern int factorial_loop(int n);

int main(void)
{
	int n, m;
	n = 12;
	m = factorial_loop(n);

	printf("%d\n", m);
}
