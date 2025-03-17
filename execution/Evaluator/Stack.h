#ifndef _EVAL_H 
#define _EVAL_H 
typedef sturct VAL_STRUCT
{
	union
	{
		int num;				// 栈中保存数值
		char op;				// 栈中保存操作符
	};
	sturct VAL_STRUCT *next;	// 下一个栈结点，栈顶结点此项为NULL
	struct VAL_STRUCT *prev;	// 上一个栈结点，栈底节点此项为NULL
} node_t;
#endif
