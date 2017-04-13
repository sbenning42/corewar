/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 10:45:42 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/13 15:46:17 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				vm_put_cycle(t_vm *vm)
{
	if (vm->config.cycle && ISBIT(vm->config.verb, VM_CYCLE_VERB))
		ft_printf("It is now cycle %u\n", vm->config.cycle);
}

void				vm_run_cycle(t_vm *vm)
{
	vm->config.cycle += 1;
	vm_put_cycle(vm);
	vm_play_process(vm);
}

int					vm_finish(t_vm *vm)
{
	if (!vm->gconfig.cycle_to_die)
		return (1);
	if (vm->config.cycle % vm->gconfig.cycle_to_die)
		return (0);
	vm_check_process(vm);
	vm_check_live(vm);
	vm_check_checks(vm);
	ft_lstdel_if(&vm->process, NULL, vm_is_process_dead, vm_del_process);
	return ((vm->process ? 0 : 1));
}

void				vm_loop(t_vm *vm)
{
	if (vm->config.nb_player < 1)
		return ;
	while (42)
	{
		vm_run_cycle(vm);
		if (vm_finish(vm))
			break ;
	}
}

void				vm_cleanup(t_vm *vm)
{
	vm_put_memory(vm);
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
