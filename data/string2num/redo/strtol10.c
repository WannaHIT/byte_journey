#include <stdio.h>

const int Trans[6][8] = {
    //      0     1-9    '-'    x|X    a-f    A-F    ' '   other
    {1, 2, 3, -1, 5, 5, 0,  -1},
    {2, 2, 6, 5,  5, 6, 6,  6},
    {2, 2, 6, 6,  5, 5, 6,  6},
    {1, 2,-1, -1, 5, 5, -1, -1},
    {5, 5,-1,-1,  5, 5, -1,-1},
    {5, 5,6,  6,  5, 5,  6,6,},
};

int get_inputnum(char c)
{
    if(c=='0')              return 0;
    if(c>='1' && c<='9')    return 1;
    if(c == '-')            return 2;
    if(c == 'x' || c=='X')  return 3;
    if(c>='a' && c<='f')    return 4;
    if(c>='A' && c<='F')    return 5;
    if(c == ' ')            return 6;
    return 7;
}

int string2num(char *str, int *val)
{
    int i=0, _state=0, state=0, neg=0, dec=0, hex=0;
    char c;
    while(1)
    {
        c = str[i];
        _state = state;
        state = Trans[_state][get_inputnum(c)];

        switch(state) // 7个状态
        {
            case 0:
                break;
            case 1:
                break;
            case 2:
                dec = dec * 10 + (c - '0');
                hex = hex * 16 + (c - '0');
                break;
            case 3:
                neg = 1;
                break;
            case 4:
                break;
            case 5:
                hex = hex * 16 + 
                    ((c>='0' && c<='9') ? (c-'0')  : 0) +
                    ((c>='a' && c<='f') ? (c-'a'+10): 0) +
                    ((c>='A' && c<='F') ? (c-'A'+10): 0);
                    break;
            case 6:
                if(_state==0) *val = 0;
                else if(_state == 2) *val = dec;
                else if(_state == 5) *val = hex;
                else return 0; // failed
                if(neg == 1) *val = (*val) * (-1);
                return 1;
        }
        ++i;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int a = 0;
    int s = 0;
    s = string2num(argv[1], &a);
    
    if(s==1)
        printf("%s is %d\n", argv[1], a);
    else 
        printf("FAILED.\n");

    return 0;
}