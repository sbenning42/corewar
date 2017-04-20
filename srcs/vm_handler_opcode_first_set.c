/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handler_opcode_first_set.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:36:06 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/20 16:16:49 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_handler_opcode_live(t_vm *vm, t_process *p, t_instruction *ins)
{
	int			id;

	p->live = 0;
	vm_put_instruction(vm, p, ins);
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

	i_op1 = ins->args[0].value;
	i_op2 = ins->args[1].value;
	i_res = ins->args[2].value;
	if (check_reg_index(vm, i_op1) || check_reg_index(vm, i_op2) || check_reg_index(vm, i_res))
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	p->registre[i_res] = p->registre[i_op1] + p->registre[i_op2];
	if (!p->registre[i_res])
		p->carry = 1;
	else
		p->carry = 0;
	vm_put_instruction(vm, p, ins);
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void	vm_handler_opcode_sub(t_vm *vm, t_process *p, t_instruction *ins)
{
	int			i_res;
	int			i_op1;
	int			i_op2;

	i_op1 = ins->args[0].value;
	i_op2 = ins->args[1].value;
	i_res = ins->args[2].value;
	if (check_reg_index(vm, i_op1) || check_reg_index(vm, i_op2) || check_reg_index(vm, i_res))
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	p->registre[i_res] = p->registre[i_op1] - p->registre[i_op2];
	if (!p->registre[i_res])
		p->carry = 1;
	else
		p->carry = 0;
	vm_put_instruction(vm, p, ins);
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void	vm_handler_opcode_aff(t_vm *vm, t_process *p, t_instruction *ins)
{
	int	index;

	index = ins->args[0].value;
	if (check_reg_index(vm, index))
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	if (vm->config.aff > 0)
		ft_printf("%c", p->registre[index] % 256);
	vm_put_instruction(vm, p, ins);
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void		vm_handler_opcode_zjmp(t_vm *vm, t_process *p, t_instruction *ins)
{
	int				offset;

	offset = ins->args[0].value;
	offset %= vm->gconfig.idx_mod;
	vm_put_instruction(vm, p, ins);
	if (p->carry)
	{
		//vm_put_pc_move(vm, p->pc, offset, ins);
		p->pc = vm_pc(vm, p->pc + offset);
	}
	else
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
	}
}
