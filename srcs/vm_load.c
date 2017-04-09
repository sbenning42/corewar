#include "vm.h"

void            vm_load_config(void)
{
    t_vm_config *conf;

    vv_enter("vm_load_config");
    conf = &VM_A_CONFIG;
    conf->max_player = MAX_PLAYERS;
    conf->mem_size = MEM_SIZE;
    conf->max_player_size = CHAMP_MAX_SIZE;
    conf->reg_number = REG_NUMBER;
    conf->reg_size = REG_SIZE;
    conf->idx_mod = IDX_MOD;
    conf->cycle_to_die = CYCLE_TO_DIE;
    conf->nbr_live_check = NBR_LIVE;
    conf->cycle_delta = CYCLE_DELTA;
    conf->max_checks = MAX_CHECKS;
    conf->dump = -1;
    vv_quit("vm_load_config");
}

void            vm_load_arguments(void)
{
    t_lexem     *l;

    vv_enter("vm_load_arguments");
    while ((l = ft_get_arg()))
    {
        arg_dispatch(l->id)(l->value);
        lexem_del(&l);
    }
    ft_del_opt();
    vv_quit("vm_load_arguments");
}

void            vm_load_memory(void)
{
    t_cbuff     *memory;

    vv_enter("vm_load_memory");
    memory = &VM_A_MEMORY;
    if (cbuff_init(memory, VM_A_CONFIG.mem_size, VM_A_CONFIG.max_player_size))
        vm_fatal(VM_EMALLOC);
    vv_quit("vm_load_memory");
}

void            vm_load_player(void)
{
    vv_enter("vm_load_player");
    ft_lstiter(VM_A_PLAYER, vm_load_player_i);
    vv_quit("vm_load_player");
}

void            vm_load_root_process(void)
{
    vv_enter("vm_load_root_process");
    vv_msg("TODO");
    vv_quit("vm_load_root_process");
}
