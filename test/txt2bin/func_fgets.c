#include<stdio.h>
// fgets 用于从文件中读取一行文本。
// char *fgets(char *str, int n, FILE *stream);
// str: 存储读取文本的字符数组
// n: 最大读取字符数（包含结束符）
// stream: 输入文件流指针
// 成功：返回 str 参数的指针, 失败则返回NULL
int main(int argc, char *argv[])
{
	FILE *file = fopen(argv[1], "r");
	char line[100];
	while(fgets(line, 100, file) != NULL)
	{
		printf("The reading line: %s", line); // 不需要额外添加换行符
	}
	fclose(file);
	return 0;
}
