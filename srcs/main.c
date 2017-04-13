/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 10:45:42 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/13 23:41:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					vm_finish(t_vm *vm)
{
	if (vm_check_dump(vm))
		return (1);
	vm_check_step(vm);
	if (vm_check_cycle(vm))
		return (0);
	vm_check_process(vm);
	vm_check_live(vm);
	vm_check_checks(vm);
	if (!vm->process)
	{
		vm_declare_win(vm);
		return (1);
	}
	return (0);
}

void				vm_loop(t_vm *vm)
{
	if (vm->config.nb_player < 1)
		return ;
	while (42)
	{
		vm->config.cycle += 1;
		if (ISBIT(vm->config.verb, VM_CYCLE_VERB))
			vm_declare_cycle(vm);
		vm_play_process(vm);
		if (vm_finish(vm))
			break ;
	}
}

void				vm_cleanup(t_vm *vm)
{
	ft_lstdel(&vm->player, vm_del_player);
	ft_lstdel(&vm->process, vm_del_process);
}

int					main(int ac, char **av)
{
	t_vm			vm;

	set_main(ac, av);
	if (ac < 2)
		vm_fatal(VM_EUSAGE);
    vm_setup(&vm);
    vm_loop(&vm);
    vm_cleanup(&vm);
	return (0);
}
