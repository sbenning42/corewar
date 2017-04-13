/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handler_opcode_first_set.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:36:06 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/13 19:05:12 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_handler_opcode_live(t_vm *vm, t_process *p)
{
	int	arg;

	p->live = 0;
	p->pc += 1;
	arg = vm_get_direct_int_arg(p->pc);
#ifdef LINUX
	arg = INT_LITTLE2BIG(arg);
#endif
	p->pc += 4;
	vm->config.nb_live += 1;
	if (!is_available_id(vm, arg))
	{
		vm->config.last_live_id = arg;
		if (ISBIT(vm->config.verb, VM_LIVE_VERB))
			vm_declare_live(vm);
	}
	vm_set_timer(p);
}

void	vm_handler_opcode_add(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}

void	vm_handler_opcode_sub(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}

void	vm_handler_opcode_aff(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}

void	vm_handler_opcode_zjmp(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}
