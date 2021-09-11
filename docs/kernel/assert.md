# Kernel - Assert
# assert.h

Assert is a macro that can be used to check that a condition is true. It is
used to check that the program is behaving as expected. If the condition is
false, the program will abort with an error message. The macro is used like
this:
```c
#include <assert.h>

int foo(int x)
{
    assert(x > 0);
    return x;
}
```

The macro is defined in the header file `assert.h`. The kernel assert macro
is not part of the standard library. It is defined in the kernel header file
`include/assert.h`. The kernel assert macro is used to check that the kernel
is behaving as expected. If the condition is false, the kernel will send a
debug message to the kernel log and then abort.

The definition of the macro assert depends on another macro, `NDEBUG`, which
is not defined by default. If `NDEBUG` is defined, the macro is defined to
nothing. Otherwise, the macro is defined to:
```c
# define Assert(exp)  if (exp) ; \
	else assertion_failed(#exp, __FILE__, __BASE_FILE__, __LINE__)
```
You can enable or disable the NDEBUG macro inside of the build configuration. [config.cfg](../../config.cfg)

## Parameters
- exp (condition) - expression of scalar type that is evaluated to true or false

## Return value
- None

## Notes
- Because assert is a [function-like macro](), commas anywhere in `condition` that are not protected by parentheses are interpreted as argument separators.
- There is no standardized interface to add an additional message to assert errors. A portable way to include one is to use a [comma operator]() provided it has not been [overloaded]().

## Real world example:
Here is a real world example of using the kernel assert macro:
`src/arch/i386/paging.c`
```c
#include <assert.h>

...

static int virtual_write_unsafe(pdir_t *pdir, void *extern_va, void *src, size_t len)
{
    uint64_t pgoff, pa;
    size_t tot, to_write;
    void *va;

    Assert(len <= INT32_MAX);

    for (tot = 0; tot < len; extern_va += to_write, tot += to_write)
    {
        if (get_mapping2(pdir, extern_va, &pa) < 0)
            return -EFAULT;
        
        pgoff       = ((uint64_t) extern_va) & OFFSET_IN_PAGE_MASK;
        to_write    = MIN(PAGE_SIZE - pgoff, len - tot);

        va = KERNEL_PA_TO_VA(pa);
        memcpy(va, src + tot, to_write);
    }

    return (int)tot;
}

...

```

Here is a real world example from a regular user program:
```c
#include <assert.h>

int main()
{
    Assert(2 + 2 == 4);
    return 0;
}
```