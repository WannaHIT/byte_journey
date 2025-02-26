#include<stdio.h>
// #include"add.h"
#include<add.h> // gcc -I. main.c add.c
int main(void){
	int c =	add(1, 9);
	printf("Add result is %d\n", c);
	return 0;
}
