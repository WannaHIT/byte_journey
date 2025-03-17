#include<stdio.h>
#include<stdlib.h>

#include"Stack.h"

/// @brief 向栈中压入新的值
/// @param stack 栈顶结点
/// @param val 压入的值，可以为操作符op, stack.num 与stack.op地址相同
/// @return 新的栈顶结点
node_t *stack_push(node_t *stack, int val)
{
	if(stack==NULL)
		stack = calloc(1, sizeof(node_t));
	else{
		stack->next = calloc(1, sizeof(node_t));
		stack->next->prev = stack;
		stack = stack->next;
	}
	stack->num = val;		// 等价于stack->op = (char)val
	stack->next = NULL;
	return stack;
}


/// @brief 从栈中弹出栈顶的值
/// @param stack 栈顶结点
/// @return 弹出后的栈顶结点
node_t *stack_pop(node_t *stack)
{
	node_t *prev = stack->prev;
	free(stack);
	if(prev != NULL)
		prev->next = NULL;
	return prev;
}
