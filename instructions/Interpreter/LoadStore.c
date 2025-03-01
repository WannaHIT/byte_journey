#include<stdint.h>

// va2pa的函数指针类型， 用于函数指针参数传递
typedef uint64_t (*va2pa_t)(uint64_t);

/// @brief 将数据写入内存的有效地址
/// @param mem 指向译物理内存的指针
/// @param va2pa_store 指向译va2pa_store的函数指针
/// @param va2pa_laod 指向译va2pa_laod的函数指针
/// @param mem 指向译物理内存的指针