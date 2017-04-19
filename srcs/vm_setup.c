/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:14:41 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/19 16:23:35 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char		*g_key[] = {\
    "Affiche",\
    "Dump",\
    "Step Run",\
    "Player Number",\
    "Verbosity",\
    "Numbers",\
    "Champions"\
};

static char		*g_regex[] = {\
    "\\-+[affiche|a]",\
    "\\-+[dump|d]",\
    "\\-+[step|s]",\
    "\\-+[number|n]",\
    "\\-+[verbose|v]",\
    "\\-?[0-9]+",\
    ".*"\
};

static void		vm_load_gconfig(t_vm *vm)
{
	vm->gconfig.max_player = MAX_PLAYERS;
	vm->gconfig.mem_size = MEM_SIZE;
	vm->gconfig.champ_max_size = CHAMP_MAX_SIZE;
	vm->gconfig.reg_number = REG_NUMBER;
	vm->gconfig.reg_size = REG_SIZE;
	vm->gconfig.idx_mod = IDX_MOD;
	vm->gconfig.cycle_to_die = CYCLE_TO_DIE;
	vm->gconfig.cycle_delta = CYCLE_DELTA;
	vm->gconfig.max_checks = MAX_CHECKS;
	vm->gconfig.nbr_live = NBR_LIVE;
}

void			vm_setup(t_vm *vm)
{
	ft_bzero(vm, sizeof(*vm));
	vm->config.dump = -1;
	vm->config.step = -1;
	vm->config.last_live_id = -1;
	vm_load_gconfig(vm);
    set_args(g_key, g_regex, TABSIZE(g_regex));
	vm_load_args(vm);
	if (vm->config.nb_player < 1)
		vm_fatal(VM_EUSAGE);
	vm_load_process(vm);
}
