#include "vm.h"

void            vm_rec_load_binary(t_list *l, int i, size_t offset)
{
    t_player    *p;
    size_t      start;

    if (!l)
        return ;
    vv_enter("vm_rec_load_binary");
    p = (t_player *)l->content;
    if (p->id < 0)
    {
        vm_rec_load_binary(l->next, i + 1, offset);
        return ;
    }
    start = offset * i;
    p->pc = VM_A_MEMORY.buffer + start;
    ft_memcpy(p->pc, p->obj_file->binary + sizeof(header_t), p->obj_file->binary_size - sizeof(header_t));
    vm_rec_load_binary(l->next, i + 1, offset);
    vv_quit("vm_rec_load_binary");
}

void            vm_load_binary(void)
{
    size_t      offset;

    vv_enter("vm_load_binary");
    if (VM_A_CONFIG.nb_player < 1)
        return ;
    offset = VM_A_CONFIG.mem_size / VM_A_CONFIG.nb_player;
    vm_rec_load_binary(VM_A_PLAYER, 0, offset);
    vv_quit("vm_load_binary");
}
