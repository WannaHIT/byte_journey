#include<stdint.h>
extern const uint64_t MEMORY_SIZE;
/// @brief 只有Load指令可以使用该函数!
/// 将虚拟地址vaddr转换为物理地址paddr
/// @param vaddr 虚拟地址
/// @return 物理地址
uint64_t va2pa_l(uint64_t vaddr) {return vaddr % MEMORY_SIZE; }

/// @brief 只有Store指令可以使用该函数!
/// 将虚拟地址vaddr转换为物理地址paddr
/// @param vaddr  虚拟地址
/// @return 物理地址
uint64_t va2pa_s(uint64_t vaddr) { return vaddr % MEMORY_SIZE; }