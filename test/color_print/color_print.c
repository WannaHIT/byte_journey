#include <stdio.h>
// 在终端打印不同的颜色
int main() {
    int arr[] = {10, 20, 30, 40, 50, 60};

    // 黑色
    printf("\033[1;30m%d\033[0m\n", arr[0]); // 黑色

    // 红色
    printf("\033[1;31m%d\033[0m\n", arr[1]); // 红色

    // 绿色
    printf("\033[1;32m%d\033[0m\n", arr[2]); // 绿色

    // 黄色
    printf("\033[1;33m%d\033[0m\n", arr[3]); // 黄色

    // 蓝色
    printf("\033[1;34m%d\033[0m\n", arr[4]); // 蓝色

    // 品红色
    printf("\033[1;35m%d\033[0m\n", arr[5]); // 品红色
	
	// 青绿色 
	printf("\033[1;36m%d\033[0m\n", arr[5]); // 品红色

    return 0;
}
