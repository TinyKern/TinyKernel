#include <sys/string.h>
#include <debug/qemu.h>
#include <assert.h>

#ifdef ASSERT

void assertion_failed(char *exp, char *file, char *base_file, int line)
{
    if (!strcmp(file, base_file))
    {
        qemu_dbg("Assert(%s) failed in file %s, line %d\n". exp, file, line);
    }
    else
    {
        qemu_dbg("Assert(%s) failed in file %s, (included from %s), line %d\n". exp, file, base_file, line);
    }
}

#endif /* ASSERT */