/// @breif 对二元运算求值
/// @param left 左输入
/// @param right 右输入
/// @param op 操作符
/// @return 求值结果
int binary_eval(int left, int right)
{
	switch (op) {
		case '+': return left + right;
		case '-': return left - right;
		case '*': return left * right;
		case '/': return left / right;
		default: return 0;
	}
}
