/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handler_opcode_second_set.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:55:51 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/14 14:30:46 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_handler_opcode_and(t_vm *vm, t_process *p)
{
	unsigned char	*pc;
	unsigned char	ocp;
	int				size;
	int				arg1;
	int				arg2;
	int				val;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 1;
	ocp = *pc;
	pc += 1;
	arg1 = vm_get_multi_arg(pc, ocp, &size, 4);
	if (size == 1)
		arg1 = p->registre[arg1];
	pc += size;
	ocp <<= 0x02;
	arg2 = vm_get_multi_arg(pc, ocp, &size, 4);
	if (size == 1)
		arg2 = p->registre[arg2];
	pc += size;
	ocp <<= 0x02;
	val = arg1 & arg2;
	if (!val)
		p->carry = 1;
	else
		p->carry = 0;
	p->registre[vm_get_register_arg(pc)] = val;
	pc += 1;
	p->pc += (pc - p->pc);
	vm_set_timer(p);
	(void)vm;
}

void	vm_handler_opcode_or(t_vm *vm, t_process *p)
{
	unsigned char	*pc;
	unsigned char	ocp;
	int				size;
	int				arg1;
	int				arg2;
	int				val;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 1;
	ocp = *pc;
	pc += 1;
	arg1 = vm_get_multi_arg(pc, ocp, &size, 4);
	if (size == 1)
		arg1 = p->registre[arg1];
	pc += size;
	ocp <<= 0x02;
	arg2 = vm_get_multi_arg(pc, ocp, &size, 4);
	if (size == 1)
		arg2 = p->registre[arg2];
	pc += size;
	ocp <<= 0x02;
	val = arg1 | arg2;
	if (!val)
		p->carry = 1;
	else
		p->carry = 0;
	p->registre[vm_get_register_arg(pc)] = val;
	pc += 1;
	p->pc += (pc - p->pc);
	vm_set_timer(p);
}

void	vm_handler_opcode_xor(t_vm *vm, t_process *p)
{
	unsigned char	*pc;
	unsigned char	ocp;
	int				size;
	int				arg1;
	int				arg2;
	int				val;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 1;
	ocp = *pc;
	pc += 1;
	arg1 = vm_get_multi_arg(pc, ocp, &size, 4);
	if (size == 1)
		arg1 = p->registre[arg1];
	pc += size;
	ocp <<= 0x02;
	arg2 = vm_get_multi_arg(pc, ocp, &size, 4);
	if (size == 1)
		arg2 = p->registre[arg2];
	pc += size;
	ocp <<= 0x02;
	val = ((arg1 & ~arg2) | (~arg1 & arg2));
	if (!val)
		p->carry = 1;
	else
		p->carry = 0;
	p->registre[vm_get_register_arg(pc)] = val;
	pc += 1;
	p->pc += (pc - p->pc);
	vm_set_timer(p);
}
