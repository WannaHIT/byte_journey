#include<stdio.h>
#include<stdint.h>
// size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
// ptr: 要写入的数据的指针
// size: 每个元素的字节大小
// nmemb: 要写入的元素个数
// stream: 输出文件流指针
// 返回值：成功写入的元素数量（不是字节数）
int main(void)
{
	FILE *file = fopen("./data.bin", "wb");
	uint32_t numbers[] = {0x12345678, 0xAABBCCDD};
	// 写入2个uint32_t整数
	fwrite(numbers, sizeof(uint32_t), 2, file);
	fclose(file);
	// 或者等价于:
	// fwrite(numbers, 4, 2, file);
	// 或者:
	// fwrite(&numbers[0], 1, 8, file);
	return 0;
}
