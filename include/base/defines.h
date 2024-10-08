#ifndef DEFINES_H_
#define DEFINES_H_

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <uchar.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef char16_t c16;
typedef int32_t b32;
typedef char byte;
typedef uintptr_t uptr;
typedef ptrdiff_t isize;
typedef size_t usize;

static_assert(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
static_assert(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
static_assert(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
static_assert(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");
static_assert(sizeof(i8) == 1, "Expected i8 to be 1 byte.");
static_assert(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");
static_assert(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
static_assert(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");
static_assert(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");
static_assert(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

#if defined(__clang__)
#define COMPILER_CLANG
#elif defined(_MSC_VER)
#define COMPILER_CL
#elif defined(__GNUC__)
#define COMPILER_GCC
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define PLATFORM_WIN
#elif defined(__linux__) || defined(__gnu_linux__)
#define PLATFORM_LINUX
#else
#error "The codebase only supports windows and linux for now"
#endif

#if defined(COMPILER_CLANG)
#define FILE_NAME __FILE_NAME__
#else
#define FILE_NAME __FILE__
#endif

#if defined(COMPILER_CL)
#define THREAD_LOCAL __declspec(thread)
#elif defined(COMPILER_GCC) || defined(COMPILER_CLANG)
#define THREAD_LOCAL __thread
#endif

#define countof(a) (sizeof(a) / sizeof(*(a)))
#define lengthof(s) (countof(s) - 1)

#define GB(count) (u64)(count * 1024 * 1024 * 1024)
#define MB(count) (u64)(count * 1024 * 1024)
#define KB(count) (u64)(count * 1024)

#define min(a, b) (((a) < (b)) ? (a) : (b))
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define between(x, a, b) ((a) <= (x) && (x) <= (b))
#define clamp(x, a, b) (((x) < (a)) ? (a) : ((b) < (x)) ? (b) \
                                                        : (x))
#define clamp_top(a, b) min(a, b)
#define clamp_bot(a, b) max(a, b)
#define wrap(x, a, b) (((x) < (a)) ? (b) : ((b) < (x)) ? (a) \
                                                       : (x))

#define memory_copy(dest, src, size) memmove((dest), (src), (size))
#define memory_copy_struct(dest, s) memory_copy((dest), (s), min(sizeof(*(dest)), sizeof(*(s))))
#define memory_zero(ptr, size) memset((ptr), 0, (size))
#define memory_zero_type(ptr, type) memory_zero((ptr), sizeof(type))

#define align_ahead(x, b) (((x) + ((b) - 1)) & (~((b) - 1)))

#define container_of(ptr, T, member) ({                  \
    const typeof( ((T *)0)->member ) *__mptr = (ptr);    \
    (T *)( (char *)__mptr - offsetof(T, member) ); })

#endif // DEFINES_H_
