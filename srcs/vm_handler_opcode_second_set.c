/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handler_opcode_second_set.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:55:51 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/19 16:49:57 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_handler_opcode_and(t_vm *vm, t_process *p, t_instruction *ins)
{
	int				op1;
	int				op2;
	int				index;

	vm_put_instruction(vm, p, ins);
	index = ins->args[2].value;
	op1 = access_arg_value(ins->args, vm, p);
	op2 = access_arg_value(ins->args + 1, vm, p);
	p->registre[index] = op1 & op2;
	if (!p->registre[index])
		p->carry = 1;
	else
		p->carry = 0;
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void	vm_handler_opcode_or(t_vm *vm, t_process *p, t_instruction *ins)
{
	int				op1;
	int				op2;
	int				index;

	vm_put_instruction(vm, p, ins);
	index = ins->args[2].value;
	op1 = access_arg_value(ins->args, vm, p);
	op2 = access_arg_value(ins->args + 1, vm, p);
	p->registre[index] = op1 | op2;
	if (!p->registre[index])
		p->carry = 1;
	else
		p->carry = 0;
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void	vm_handler_opcode_xor(t_vm *vm, t_process *p, t_instruction *ins)
{
	int				op1;
	int				op2;
	int				index;

	vm_put_instruction(vm, p, ins);
	index = ins->args[2].value;
	op1 = access_arg_value(ins->args, vm, p);
	op2 = access_arg_value(ins->args + 1, vm, p);
	p->registre[index] = ((op1 & ~op2) | (~op1 & op2));
	if (!p->registre[index])
		p->carry = 1;
	else
		p->carry = 0;
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}
