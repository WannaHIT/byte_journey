#include <stdio.h>
#include<inttypes.h>
void test0(void)
{
    // 指针方式
    uint32_t x = 0xFFFFFFFF;
    int32_t *xp = (int32_t *)&x;
    printf("%d\n", *xp); // 输出 -1，因为以 int32_t 解读 0xFFFFFFFF。
}

void test1(void)
{
    // 值拷贝方式
    uint32_t x = 0xFFFFFFFF;
    int32_t xp = (int32_t)x;
    printf("%d\n", xp); // 输出 -1，因为值被强制转换为 int32_t。
}
int main(void)
{
    test0();

    void (*p)(void) = test1;

    p();

    return 0;
}