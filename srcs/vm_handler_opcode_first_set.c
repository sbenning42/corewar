/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handler_opcode_first_set.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:36:06 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/13 15:59:31 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_handler_opcode_live(t_vm *vm, t_process *p)
{
	int	arg;

	arg = vm_get_direct_int_arg(p->pc);
	p->pc += 5;
	vm->config.nb_live += 1;
	vm->config.last_live_id = arg;
	if (ISBIT(vm->config.verb, VM_LIVE_VERB))
		vm_declare_live(vm, arg);
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
