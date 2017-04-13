#include "vm.h"

void            vm_del_player(void *content, size_t size)
{
    free(content);
    (void)size;
}

void            vm_del_process(void *content, size_t size)
{
    free(content);
    (void)size;
}
