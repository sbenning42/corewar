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
    vv_msg("TODO: Implement death of players");
	if (vm_finish_dump())
		return (1);
	else if (vm_finish_live())
		return (1);
	else if (!VM_A_PROCESS)
	{
		vm_put_players();
        ft_print_legit_memory(VM_A_MEMORY.buffer, VM_A_CONFIG.mem_size);
		vm_declare_winner();
		return (1);
	}
    return (0);
}

int					vm_if_dead(void *ref, void *c, size_t s)
{
	return (((t_process *)c)->dead);
	(void)ref;
	(void)s;
}

void                vm_loop(void)
{
    vv_enter("vm_loop");
    while (42)
    {
		ft_lstdel_if(&VM_A_PROCESS, NULL, vm_if_dead, vm_del_process);
		ft_lstiter(VM_A_PROCESS, vm_play_process);
        VM_SINGLE->tic += 1;
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
