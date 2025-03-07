#include<stdio.h>
#include<string.h>
// 遍历一遍就可以判断并读取内容
int get_inputnum(char c)
{
	if(c == '0')				return 0;
	if(c >= '1' && c <= '9')	return 1;
	if(c == '-')				return 2;
	if(c == 'x' || c == 'X')	return 3;
	if(c >= 'a' && c <= 'f')	return 4;
	if(c >= 'A' && c <= 'F')	return 5;
	if(c == ' ')				return 6;
	return 7;
}
int transfer[6][8] = {
	// 0	1-9		-	x|X		a-f		A-F		' '		oth
	{ 1,	2,		3,	7,		5,		5,		0,		7 }, // s0: init
	{ 2,	2,		6,	4,		5,		5,		6,		6 }, // s1: First 0
	{ 2,	2,		6,	6,		5,		5,		6,		6 }, // s2: dec
	{ 1,	2,		7,	7,		5,		5,		7,		7 }, // s3: -
	{ 5,	5,		7,	7,		5,		5,		7,		7 }, // s4: x|X
	{ 5,	5,		6,	6,		5,		5,		6,		6 }  // s5: hex
};  // fuck, forget the ";"
	

// 1 Success, else 0
int string2num(char *str, int *val)
{
	int hex = 0, dec = 0, state = 0, neg = 0, i = 0, _state = 0;
	char c;

	while(1)
	{
		c = str[i];
		
		// 状态转移
		_state = state;
		state = transfer[_state][get_inputnum(c)];
		// 根据当前状态，判断是否进行计算	
		switch(state)
		{
			case 7: // failed
				return 0;
			case 2:
				dec = dec *10 + (c - '0');
				hex = hex *16 + (c - '0');
				break;
			case 3:
				neg = 1;
				break;
			case 5:
				hex = hex * 16 + 
					((c >= '0' && c <= '9') ? (c - '0') : 0) +
					((c >= 'a' && c <= 'f') ? (c - 'a' + 10) : 0) + 
					((c >= 'A' && c <= 'F') ? (c - 'A' + 10) : 0);
				break;
			case 6: // 6代表成功，根据上个状态_state来返回值
				if		( _state == 5)	*val = hex;
				else if ( _state ==1 )  *val = 0;
				else if ( _state == 2)	*val = dec;
				else return 0;	
				if(neg == 1)			*val = (*val) * -1;
				return 1;
			default:
				break;
		}
		i+=1;
	}
	return 0;
}
int main(int argc, char *argv[])
{
	int a = 0, s = 0;
	s = string2num(argv[1], &a);

	if(s == 1)
		printf("\e[1;32m [OK]'%s' ==> %d\e[0m\n", argv[1], a);
	else 
		printf("\e[1;31m [FAILED]'%s' \e[0m\n", argv[1]);
	return 0;
}
