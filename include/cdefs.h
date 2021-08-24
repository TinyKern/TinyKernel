#ifndef CDEFS_H
#define CDEFS_H

#define assert_failed(expr, file, line)

#ifdef ASSERT
# undef ASSERT
#endif // ASSERT

#ifndef NDEBUG
# define ASSERT(x)                                  \
    do {                                            \
        if (UNLIKELY(!(x)))                         \
        {                                           \
            assert_failed(#x, __FILE__, __LINE__);  \
        }                                           \
    } while (0)
#else
# define ASSERT(x) do { /* Nothing */ } while (0)
#endif // NDEBUG

#define VERIFY(x)                                   \
    do {                                            \
        if (UNLIKELY(!(x)))                         \
        {                                           \
            assert_failed(#x, __FILE__, __LINE__);  \
        }                                           \
    } while (0)

#define TO_PTR(n) ((void*)(unsigned long)(n))

#define _CONCAT(a, b)   a##b
#define CONCAT(a, b)    _CONCAT(a, b)

#define LIKELY(cond)	__builtin_expect((cond), true)
#define UNLIKELY(cond)  __builtin_expect((cond), false)

#define STATIC_ASSERT(expr)	_Static_assert(expr, "Static assertion failed");

#define IN_RANGE(addr, begin, end) ((begin) <= (addr) && (addr) < (end))

#define NORETURN __attribute__((noreturn))

#ifdef	__cplusplus
# define __BEGIN_DECLS	extern "C" {
# define __END_DECLS	}
#else
# define __BEGIN_DECLS
# define __END_DECLS
#endif

#define UNSAFE_MIN(x, y) (((x) <= (y)) ? (x) : (y))
#define UNSAFE_MAX(x, y) (((x) >= (y)) ? (x) : (y))

#define UNSAFE_MIN3(a, b, c) UNSAFE_MIN(UNSAFE_MIN((a), (b)), (c))
#define UNSAFE_MAX3(a, b, c) UNSAFE_MAX(UNSAFE_MAX((a), (b)), (c))

#define UNSAFE_ABS(x) ((x) >= 0 ? (x) : -(x))

#define MIN(a, b)                                               \
    ({                                                          \
        const typeof(a) CONCAT(_a, __LINE__) = (a);             \
        const typeof(b) CONCAT(_b, __LINE__) = (b);             \
        UNSAFE_MIN(CONCAT(_a, __LINE__), CONCAT(_b, __LINE__)); \
    })

#define MAX(a, b)                                               \
    ({                                                          \
        const typeof(a) CONCAT(_a, __LINE__) = (a);             \
        const typeof(b) CONCAT(_b, __LINE__) = (b);             \
        UNSAFE_MAX(CONCAT(_a, __LINE__), CONCAT(_b, __LINE__)); \
    })

#define MIN3(a, b, c)                                           \
    ({                                                          \
        const typeof(a) CONCAT(_a, __LINE__) = (a);             \
        const typeof(b) CONCAT(_b, __LINE__) = (b);             \
        const typeof(c) CONCAT(_c, __LINE__) = (c);             \
        UNSAFE_MIN3(CONCAT(_a, __LINE__),                       \
                    CONCAT(_b, __LINE__),                       \
                    CONCAT(_c, __LINE__));                      \
    })

#define MAX3(a, b, c)                                           \
    ({                                                          \
        const typeof(a) CONCAT(_a, __LINE__) = (a);             \
        const typeof(b) CONCAT(_b, __LINE__) = (b);             \
        const typeof(c) CONCAT(_c, __LINE__) = (c);             \
        UNSAFE_MAX3(CONCAT(_a, __LINE__),                       \
                    CONCAT(_b, __LINE__),                       \
                    CONCAT(_c, __LINE__));                      \
    })

#define ABS(x)                                                  \
    ({                                                          \
        const typeof(x) CONCAT(_x, __LINE__) = (x);             \
        UNSAFE_ABS(CONCAT(_x, __LINE__));                       \
    })

#define ARRAY_SIZE(a) ((int)(sizeof(a) / sizeof((a)[0])))

#endif // CDEFS_H