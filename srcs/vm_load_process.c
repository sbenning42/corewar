#include "vm.h"

static int      vm_unique_pid(void)
{
    static int  pid;

    pid += 1;
    return (pid);
}

void            vm_load_process_i(t_list *l)
{
    t_player    *p;
    t_process   process;
    
    vv_enter("vm_load_process_i");
    p = (t_player *)l->content;
    ft_bzero(&process, sizeof(t_process));
    process.player = p;
    process.pid = vm_unique_pid();
    process.pc = p->pc;
    ft_bzero(process.registre, sizeof(int) * REG_NUMBER);
    process.registre[0] = p->id;
    process.reg_number = REG_NUMBER;
    process.reg_size = REG_SIZE;
	vm_read_instruction(&process);
    l = ft_lstnew(&process, sizeof(t_process));
    if (!l)
        vm_fatal(VM_EMALLOC);
    ft_lstadd(&VM_A_PROCESS, l);
    vv_quit("vm_load_process_i");
}
