#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

uint8_t adder(uint8_t x, uint8_t y, uint8_t *cf, uint8_t *sf, uint8_t *of)
{
    // 确保输入只有低 4 位有效
    // KEY
    x &= 0x0F;
    y &= 0x0F;


    uint8_t a = 0;
    uint8_t ai = 0;
    uint8_t xi = 0;
    uint8_t yi = 0;
    uint8_t ci = 0;
    uint8_t cj = 0;


    for(int i=0; i< 4; i++)
    {
        ci = cj;
        xi = (x >> i) & 1;
        yi = (y >> i) & 1;

        ai = (xi ^ yi ^ ci);
        cj = (xi & yi) | ((xi ^ yi ) & ci);

        a = a | (ai << i);
    }

    *cf = (cj & 1);
    // *sf = (ai & 1);
    *sf = ((a >> 3) & 1);  // 获取结果的最高位（位 3）
    *of = (ci ^ cj) & 1;

    return a;
}


int main(int argc, char *argv[])
{
    uint8_t x = strtol(argv[1], NULL, 10);
    uint8_t y = strtol(argv[2], NULL, 10);

    uint8_t of = 0, sf = 0, cf = 0;

    uint8_t result;
    result = adder(x, y, &cf, &sf, &of);

    printf("0x%x + 0x%x = 0x%x\nCF = %u, SF = %u, OF = %u\n\n", x, y, result, cf, sf, of);

    return  0;
}