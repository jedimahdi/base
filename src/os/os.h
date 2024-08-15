#ifndef OS_H_
#define OS_H_

#include "defines.h"

//~ Memory

void *os_memory_reserve(u64 size);
void os_memory_commit(void *memory, u64 size);
void os_memory_decommit(void *memory, u64 size);
void os_memory_release(void *memory, u64 size);

#endif // OS_H_
