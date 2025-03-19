/// @breif 比较操作符a与b的优先级
/// @param a 操作符a， 当前扫描到的操作符
/// @param b 操作符b， 当前op栈顶操作符
/// @return 如果优先进行a运算，返回1, 否则为0
int op_compare(char a, char b)
{
	if((a=='/' || a=='*') && (b=='+' || b=='-'))
		return 1;
	return 0;
}
