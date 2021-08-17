#ifndef CDEFS_H
#define CDEFS_H

#if __GNUC__ >= 3
# define __glibc_unlikely(cond)	__builtin_expect ((cond), 0)
# define __glibc_likely(cond)	__builtin_expect ((cond), 1)
#else
# define __glibc_unlikely(cond)	(cond)
# define __glibc_likely(cond)	(cond)
#endif

#endif // CDEFS_H