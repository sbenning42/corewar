#include "vm.h"

int         cbuff_init(t_cbuff *cb, size_t size, size_t offset)
{
    vv_enter("cbuff_init");
    if (!(cb->buffer = ft_memalloc(size)))
        return (-1);
    cb->end = cb->buffer + size;
    cb->curs = cb->buffer;
    cb->allocated_size = size;
    cb->used_size = 0;
    cb->offset = offset;
    vv_quit("cbuff_init");
    return (0);
}

void        cbuff_cpy(t_cbuff *cb, void *src, size_t size)
{
    vv_enter("cbuff_cpy");
    if (cb->used_size + size > cb->allocated_size)
        vm_fatal(999);
    ft_memcpy(cb->buffer, src, size);
    vv_quit("cbuff_cpy");
}

void        cbuff_del(t_cbuff *cb)
{
    vv_enter("cbuff_del");
    if (cb->buffer)
        ft_memdel((void **)&cb->buffer);
    ft_bzero((void *)cb, sizeof(t_cbuff));
    vv_quit("cbuff_del");
}
