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

int                 vm_finish(void)
{
    vv_enter("vm_finish");
    vv_msg("TODO");
    if (VM_A_CONFIG.dump > 0)
    {
        if (VM_SINGLE->tic >= (unsigned long)VM_A_CONFIG.dump)
        {
            ft_print_memory(VM_A_MEMORY.buffer, VM_A_CONFIG.mem_size);
            vv_quit("vm_finish");
            return (1);
        }
    }
    vv_quit("vm_finish");
    return (1/*TODO: 0*/);
}

void                vm_loop(void)
{
    vv_enter("vm_loop");
    while (42)
    {
        VM_SINGLE->tic += 1;
        vv_msg("TODO");
        if (vm_finish())
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
    vv_quit("vm_cleanup");
}
