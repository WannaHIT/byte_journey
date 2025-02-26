int add_2(int a, int b)
{
	return a+b;
}

void main()
{
	int a = 0xabcd0000;
	int b = 0x00001234;
	int c = add_2(a, b);
}
