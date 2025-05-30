// 25.05.30
// clear the work flow

#include <stdio.h>

// ANSI 颜色代码
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

int get_input(char c)
{
    if(c == '0')                                return 0;
    if(c>='1' && c<='9')                        return 1;
    if(c == '-')                                return 2;
    if(c=='x' || c=='X')                        return 3;
    if(c>='a' && c<='f' || c>='A' && c<='F')    return 4;
    if(c == ' ')                                return 5;
    return 6;
}

const int Transfer[6][7] = {
    {1,2,  3,-1,5, 0,-1},
    {2,2,  6, 4,6, 6, 6},
    {2,2,  6, 6,5, 6, 6},
    {1,2, -1,-1,5,-1,-1},
    {5,5, -1,-1,5,-1,-1},
    {5,5,  6, 6,5, 6, 6}
};

int str2num(char *str, int *val)
{
    int i = 0, _state = 0, state = 0, neg = 0, dec = 0, hex = 0;
    char c;

    while(1)
    {
        c = str[i];
        _state = state;
        state = Transfer[_state][get_input(c)];

        switch(state)
        {
            case 0:
            case 1:
                break;
            case 2:
                dec = dec * 10 + (c - '0');
                hex = hex * 16 + (c - '0');
                break;
            case 3:
                neg = -1;
                break;
            case 4:
                break;
            case 5:
                hex = hex * 16 + (
                    ((c>='a' && c<='f') ? (c - 'a' + 10) : 0) + 
                    ((c>='A' && c<='F') ? (c - 'A' + 10) : 0) +
                    ((c>='0' && c<='9') ? (c - '0' + 0)  : 0)
                );
                break;
            case 6:
                if(_state == 2)
                    *val = dec;
                else if(_state == 5)
                    *val = hex;
                else
                    return 0;
                if(neg == 1)
                    *val = (*val) * -1;

                return 1;
                break;
            default:
                break;
        }
        i++;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int a = 0, s = str2num(argv[1], &a);
    if(s == 1)
        printf(GREEN "[OK] '%s' ==> %d\n" RESET, argv[1], a);
    else 
        printf(RED"[FAILED] '%s'\n" RESET, argv[1]);
    return 0;
}