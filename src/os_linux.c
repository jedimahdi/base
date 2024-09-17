#include "memory/arena.h"
#include "os/os.h"

#if defined(PLATFORM_LINUX)

#include "base/defines.h"
#include <dirent.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

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

s8 os_read_file(Arena *arena, char *filepath) {
  struct stat st;
  stat(filepath, &st);
  s8 result;
  result.len = st.st_size;
  result.data = make(arena, char, st.st_size);
  i32 handle = open(filepath, O_RDWR, S_IRUSR | S_IRGRP | S_IROTH);
  ssize_t read_result = read(handle, result.data, st.st_size);
  if (read_result < 0) {
    assert(0 && "Reading from file failed");
  }
  close(handle);
  return result;
}

#endif
