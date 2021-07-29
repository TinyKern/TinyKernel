#include <kernel/stivale2.h>
#include <sys/stddef.h>

/**
 * @name:   stivale2_get_tag
 * @arg:    stivale2_struct*
 * @arg:    uint64 id
 * @returns: tag with given id
 */
void *stivale2_get_tag(struct stivale2_struct* stivale2_struct, uint64_t id)
{
    // get the first tag from linked list
    struct stivale2_tag* current_tag = (void*)stivale2_struct->tags;
    // loop through all the tags
    while (current_tag)
    {
        // if current_tag's id matches the requested id, then return the tag
        if (current_tag->identifier == id)
            return current_tag;
        // move to next tag
        current_tag = (void*)current_tag->next;
    }
    // no such tag found
    return NULL;
}