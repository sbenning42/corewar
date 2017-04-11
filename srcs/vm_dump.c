#include "vm.h"

static void     vm_dump_config(int fd)
{
    t_vm_config config;

    vv_enter("vm_dump_config");
    ft_fprintf(fd, "%s: VM Configuration:\n\n", proginfo()->name);
    config = VM_A_CONFIG;
    ft_fprintf(fd, VM_CONFIG_DUMP,\
            "Mode", config.mode,\
            "Nombre de Joueur", config.nb_player,\
            "Nombre de joueur Max", config.max_player,\
            "Memory Size", config.mem_size,\
            "Max Player Size", config.max_player_size,\
            "Max Process per Player", config.max_process,\
            "Number Register", config.reg_number,\
            "Register Size", config.reg_size,\
            "IDX Modulo", config.idx_mod,\
            "Cycle To Die", config.cycle_to_die,\
            "Cycle Delta", config.cycle_delta,\
            "Max Checks", config.max_checks,\
            "Number of Live", config.nbr_live,\
            "Live since Last Checks", config.nbr_live_check,\
            "Last Player Alive", config.id_last_live, config.name_last_live,\
            "Dump", config.dump,\
            VV_SEPLINE\
            );
    vv_quit("vm_dump_config");
}

static void     vm_dump_memory(int fd)
{
    t_cbuff     buff;

    vv_enter("vm_dump_memory");
    ft_fprintf(fd, "%s: VM Memory:\n\n", proginfo()->name);
    buff = VM_A_MEMORY;
    ft_fprintf(fd, VM_MEMORY_DUMP,\
            "Buffer", buff.buffer,\
            "Buffer End", buff.end,\
            "Cursor", buff.curs,\
            "Allocated Size", buff.allocated_size,\
            "Used Size", buff.used_size,\
            "Offset", buff.offset,\
            VV_SEPLINE\
            );
    ft_fprintf(fd, "\n");
    ft_print_memory(buff.buffer, buff.allocated_size);
    ft_fprintf(fd, "\n%s", VV_SEPLINE);
    (void)buff;
    vv_quit("vm_dump_memory");
}

static void     vm_dump_player(int fd)
{
    vv_enter("vm_dump_player");
    ft_fprintf(fd, "%s: VM Player:\n\n", proginfo()->name);
    ft_lstiter(VM_A_PLAYER, vm_dump_player_i);
    ft_fprintf(fd, "\n%s", VV_SEPLINE);
    vv_quit("vm_dump_player");
}

static void     vm_dump_process(int fd)
{
    t_list      *l;
    t_process   *p;

    vv_enter("vm_dump_process");
    ft_fprintf(fd, "%s: VM Process:\n\n", proginfo()->name);
    l = VM_A_PROCESS;
    while (l)
    {
        ft_printf("\tProcess:\n");
        p = (t_process *)l->content;
        ft_fprintf(fd, VM_PROCESS_DUMP,\
                "PID", p->pid, "PC", p->pc, "Player", p->player, "Registre", p->registre,\
                "Number Registre", p->reg_number, "Registre Size", p->reg_size,\
                "Carry Value", p->carry, "Timer", p->timer, "Error", p->error,\
                "Instruction", p->instruction,\
                "Last Instruction", p->last_instruction,\
                "Size Instruction", p->size_instruction, "Tic Stamp", p->tic\
                );
        l = l->next;
    }
    ft_fprintf(fd, "\n%s", VV_SEPLINE);
    vv_quit("vm_dump_process");
}

void        vm_dump(int fd)
{
    vm_dump_config(fd);
    vm_dump_memory(fd);
    vm_dump_player(fd);
    vm_dump_process(fd);
}
