#include "defines.h"

#include <stdlib.h>
#include <sys/mman.h>

void *os_memory_reserve(u64 size) {
  return mmap(NULL, size, PROT_NONE, MAP_PRIVATE | MAP_ANON, -1, 0);
}

void os_memory_commit(void *memory, u64 size) {
  mprotect(memory, size, PROT_READ | PROT_WRITE);
}

void os_memory_decommit(void *memory, u64 size) {
  mprotect(memory, size, PROT_NONE);
}

void os_memory_release(void *memory, u64 size) {
  munmap(memory, size);
}
