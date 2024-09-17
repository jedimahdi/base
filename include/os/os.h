#ifndef OS_H_
#define OS_H_

#include "base/defines.h"
#include "base/str.h"
#include "memory/arena.h"

//~ Memory

void *os_memory_reserve(u64 size);
void os_memory_commit(void *memory, u64 size);
void os_memory_decommit(void *memory, u64 size);
void os_memory_release(void *memory, u64 size);

//~ Files

s8 os_read_file(Arena *arena, char *filepath);

#endif // OS_H_
