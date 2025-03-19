#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Stack.h"

// 外部函数
extern node_t *stack_push(node_t *stack, int val);
extern node_t *stack_pop(node_t *stack);
extern int binary_eval(int left, int right, char op);
extern int op_compare(char a, char b);

// 求值器入口
int main(int argc, char *argv[])
{

}
