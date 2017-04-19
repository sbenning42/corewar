/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handler_opcode_first_set.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:36:06 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/19 16:44:31 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_handler_opcode_live(t_vm *vm, t_process *p, t_instruction *ins)
{
	int			id;

	vm_put_instruction(vm, p, ins);
	p->live = 0;
	vm->config.nb_live += 1;
	id = ins->args[0].value;
	if (!is_available_id(vm, id))
	{
		vm->config.last_live_id = id;
		if (ISBIT(vm->config.verb, VM_LIVE_VERB))
			vm_declare_live(vm, p->id);
	}
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void	vm_handler_opcode_add(t_vm *vm, t_process *p, t_instruction *ins)
{
	int			i_res;
	int			i_op1;
	int			i_op2;

	vm_put_instruction(vm, p, ins);
	i_op1 = ins->args[0].value;
	i_op2 = ins->args[1].value;
	i_res = ins->args[2].value;
	p->registre[i_res] = p->registre[i_op1] + p->registre[i_op2];
	if (!p->registre[i_res])
		p->carry = 1;
	else
		p->carry = 0;
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void	vm_handler_opcode_sub(t_vm *vm, t_process *p, t_instruction *ins)
{
	int			i_res;
	int			i_op1;
	int			i_op2;

	vm_put_instruction(vm, p, ins);
	i_op1 = ins->args[0].value;
	i_op2 = ins->args[1].value;
	i_res = ins->args[2].value;
	p->registre[i_res] = p->registre[i_op1] - p->registre[i_op2];
	if (!p->registre[i_res])
		p->carry = 1;
	else
		p->carry = 0;
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void	vm_handler_opcode_aff(t_vm *vm, t_process *p, t_instruction *ins)
{
	int	index;

	vm_put_instruction(vm, p, ins);
	index = ins->args[0].value;
	if (vm->config.aff > 0)
		ft_printf("%c", p->registre[index] % 256);
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void		vm_handler_opcode_zjmp(t_vm *vm, t_process *p, t_instruction *ins)
{
	int				offset;

	vm_put_instruction(vm, p, ins);
	offset = ins->args[0].value;
	offset %= vm->gconfig.idx_mod;
	if (p->carry)
	{
		vm_put_pc_move(vm, p->pc, offset, ins);
		p->pc = vm_pc(vm, p->pc + offset);
	}
	else
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
	}
}
