/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:11:35 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/20 13:40:31 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_check_process_i(t_vm *vm, t_process *p)
{
	if (p->live >= vm->gconfig.cycle_to_die)
	{
		p->dead = 1;
		if (ISBIT(vm->config.verb, VM_DEATH_VERB))
			ft_printf("Process %lld hasn't lived for %u cycles (CTD %u)\n",\
					p->id,\
					p->live,\
					vm->gconfig.cycle_to_die);
	}
}

void		vm_check_process(t_vm *vm)
{
	t_list	*l;

	l = vm->process;
	while (l)
	{
		vm_check_process_i(vm, (t_process *)l->content);
		l = l->next;
	}
	ft_lstdel_if(&vm->process, NULL, vm_is_process_dead, vm_del_process);
}

void		vm_check_live(t_vm *vm)
{
	if (vm->config.nb_live >= vm->gconfig.nbr_live)
	{
		if (vm->gconfig.cycle_to_die > vm->gconfig.cycle_delta)
			vm->gconfig.cycle_to_die -= vm->gconfig.cycle_delta;
		else
			vm->gconfig.cycle_to_die = 0;
		if (ISBIT(vm->config.verb, VM_CYCLE_VERB))
			ft_printf("Cycle to die is now %d (nb_live)\n", vm->gconfig.cycle_to_die);
		vm->config.nb_check = 0;
	}
	else
		vm->config.nb_check += 1;
	vm->config.nb_live = 0;
}

void		vm_check_checks(t_vm *vm)
{
	if (vm->config.nb_check >= vm->gconfig.max_checks)
	{
		if (vm->gconfig.cycle_to_die > vm->gconfig.cycle_delta)
			vm->gconfig.cycle_to_die -= vm->gconfig.cycle_delta;
		else
			vm->gconfig.cycle_to_die = 0;
		if (ISBIT(vm->config.verb, VM_CYCLE_VERB))
			ft_printf("Cycle to die is now %d (check)\n", vm->gconfig.cycle_to_die);
		vm->config.nb_check = 0;
	}
}
