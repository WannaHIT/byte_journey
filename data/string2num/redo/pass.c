// PASS, totally copy, not redo 
// long strtol(const char *nptr, char **endptr, int base);
#include <stdio.h>

const int Transfer[6][8] = {
    { 1,	2,		3,	7,		5,		5,		0,		7 }, // s0: init
	{ 2,	2,		6,	4,		5,		5,		6,		6 }, // s1: First 0
	{ 2,	2,		6,	6,		5,		5,		6,		6 }, // s2: dec
	{ 1,	2,		7,	7,		5,		5,		7,		7 }, // s3: -
	{ 5,	5,		7,	7,		5,		5,		7,		7 }, // s4: x|X
	{ 5,	5,		6,	6,		5,		5,		6,		6 }  // s5: hex
};

int get_inputnum(char c)
{
    // ...
    if(c == '0')            return 0;
    if('1'<=c && c<='9')    return 1;
    if(c == '-')            return 2;
    if(c=='x' || c=='X')    return 3;
    if('a'<=c && c <='f')   return 4;
    if('A'<=c && c <='F')   return 5;
    if(c == ' ')            return 6;
    return 7;
}

int string2num(char *str, int *val)
{
    // ...
    int state = 0, i = 0, _state = 0, hex = 0, dec = 0, neg = 0;
    char c;
    while(1)
    {
        c = str[i];
        _state = state;
        state = Transfer[_state][get_inputnum(c)];
        switch(state)
        {
            case 7:
                return 0;
            case 2:
                dec = dec * 10 + (c - '0');
                hex = hex * 16 + (c - '0');
                break;
            case 3:
                neg = 1;
                break;
            case 5:
                hex = hex * 16 +
                    (('0'<=c && c<='9')  ? (c - '0'   ) : 0 )+
                    (('a'<=c && c <='f') ? (c - 'a' + 10): 0) +
                    (('A'<=c && c <='F') ? (c - 'A' + 10) : 0);
                break;
            case 6:
                if          (_state == 5)     *val = hex;
                else if     ( _state ==1 )      *val = 0;
                else if     (_state == 2)     *val = dec;
                else return 0;
                if(neg == 1) *val = (*val) * -1;
                return 1;
            default:    break;
        }
        ++i;
    }
    return 0;
}


int main(int argc, char *argv[])
{
    int a = 0, s = string2num(argv[1], &a);

    if(s == 1)  printf("\e[1;32m[OK] '%s' ==> %d\e[0m\n", argv[1], a);
    else
                printf("\e[1;31m[FAILED] '%s'\e[0m\n", argv[1]);
    return 0;
}