#include "vm.h"

t_vm                *s_vm(void)
{
    static t_vm     vm;

    return (&vm);
}

void                vm_setup(void)
{
    vv_enter("vm_setup");
    ft_bzero((void *)VM_SINGLE, sizeof(t_vm));
    vm_load_config();
    vm_load_arguments();
    vm_load_memory();
    vm_load_player();
    vm_load_binary();
    vm_load_root_process();
    vv_dump();
    vv_quit("vm_setup");
}

void                vm_loop(void)
{
    vv_enter("vm_loop");
    while (42)
    {
        vv_msg("TODO");
        break ;
    }
    vv_quit("vm_loop");
}

void                vm_cleanup(void)
{
    vv_enter("vm_cleanup");
    ft_lstdel(&VM_A_PLAYER, vm_del_player);
    ft_lstdel(&VM_A_PROCESS, vm_del_process);
    cbuff_del(&VM_A_MEMORY);
//    vv_dump();
    vv_quit("vm_cleanup");
}
