#include "vm.h"

void            vm_del_player(void *content, size_t size)
{
    t_player    *player;

    vv_enter("vm_del_player");
    player = (t_player *)content;
    close_file(&player->obj_file);
    free(player);
    vv_quit("vm_del_player");
    (void)size;
}

static void     vm_del_instruction(t_instruction **i)
{
    if ((*i)->code)
        ft_memdel((void **)&(*i)->code);
    ft_memdel((void **)i);
}

void            vm_del_process(void *content, size_t size)
{
    t_process   *process;

    vv_enter("vm_del_process");
    process = (t_process *)content;
    if (process->instruction)
        vm_del_instruction(&process->instruction);
    if (process->last_instruction)
        ft_memdel((void **)&process->last_instruction);
    free(process);
    vv_quit("vm_del_process");
    (void)size;
}
