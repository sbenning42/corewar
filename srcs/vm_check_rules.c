/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_check_rules.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 19:32:58 by                   #+#    #+#             */
/*   Updated: 2017/04/18 13:20:47 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					vm_check_dump(t_vm *vm)
{
	if ((vm->config.dump > 0)\
			&& (vm->config.cycle_tot == vm->config.dump))
	{
		vm_put_memory(vm);
		return (1);
	}
	return (0);
}

void				vm_check_step(t_vm *vm)
{
	char			*null;

	null = NULL;
	if (vm->config.step < 1)
		return ;
	if (!(vm->config.cycle_tot % (size_t)vm->config.step))
	{
		vm_put_memory(vm);
		get_next_line(0, &null);
		if (null)
			ft_memdel((void **)&null);
	}
}

int					vm_check_cycle(t_vm *vm)
{
	if ((vm->gconfig.cycle_to_die > 0)\
			&& (vm->config.cycle != vm->gconfig.cycle_to_die))
	   return (1);
	vm->config.cycle = 0;
	return (0);
}
