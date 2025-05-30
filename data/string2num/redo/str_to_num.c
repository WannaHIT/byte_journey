// 25.05.29 

#include <stdio.h>

// ANSI 颜色代码
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"

int get_input(char c)
{
    if(c == '0')                                    return 0;
    if(c>='1' && c<='9')                            return 1;
    if(c == '-')                                    return 2;
    if(c == 'x' ||c == 'X')                         return 3;
    if(c>='a' && c<='f' || c>='A' && c<='F')        return 4;
    if(c == ' ')                                    return 5;
    else                                            return 6;
}
const int Transfer[6][7] = {
    {1,2,  3,-1,5, 0,-1},
    {2,2,  6, 4,6, 6, 6},
    {2,2,  6, 6,5, 6, 6},
    {1,2, -1,-1,5,-1,-1},
    {5,5, -1,-1,5,-1,-1},
    {5,5,  6, 6,5, 6, 6}
};

// 返回值是一个状态 1代表转换成功, 0 代表失败
// 转换后的值通过传入的参数指针返回
int string2num(char *str,int *val)
{
    int i = 0, state = 0, _state = 0, neg = 0, hex = 0, dec = 0;
    char c;
    
    // One time scan
    while(1)
    {
        c = str[i];  // 这个涉及到break
        _state = state;
        state = Transfer[_state][get_input(c)];
        // 根据不同的状态对 c 进行操作
        // 判断是否进行数值计算
        switch(state)
        {
            case -1:
                return 0; // 失败的时候返回 0

            case 0:
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
                hex = hex * 16 + (
                    ((c>='0' && c<='9')? (c - '0'      ) : 0) + 
                    ((c>='a' && c<='f')? (c - 'a' + 10 ) : 0) +
                    ((c>='A' && c<='F')? (c - 'A' + 10 ) : 0)
                );
                break;
            case 6:
            // 根据成功之前的那个状态判断是十进制还是十六进制
                if      (_state == 5) *val = hex;
                else if (_state == 2) *val = dec;
                else return 0;  // fail

                if(neg == 1) *val = (*val) * -1;
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
    int a = 0, s = string2num(argv[1], &a);
    if(s == 1)
        printf(GREEN "[OK] '%s' ==> %d\n" RESET, argv[1], a);
    else 
        printf(RED"[FAILED] '%s'\n" RESET, argv[1]);
    return 0;
}