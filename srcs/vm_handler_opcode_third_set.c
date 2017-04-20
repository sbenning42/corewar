/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handler_opcode_third_set.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:56:52 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/20 09:58:47 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_handler_opcode_ld(t_vm *vm, t_process *p, t_instruction *ins)
{
	int	value;
	int	index;
	int	err;

	index = ins->args[1].value;
	if (check_reg_index(vm, index))
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	value = access_arg_value(ins->args, vm, p, &err);
	if (err)
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	p->registre[index] = value;
	if (!p->registre[index])
		p->carry = 1;
	else
		p->carry = 0;
	vm_put_instruction(vm, p, ins);
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void	vm_handler_opcode_st(t_vm *vm, t_process *p, t_instruction *ins)
{
	int	pc;
	int	index;
	int	offset;
	int	value;
	int	err;

	value = access_arg_value(ins->args, vm, p, &err);
	if (err)
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	if (ins->args[1].type == reg_arg)
	{
		index = ins->args[1].value;
		if (check_reg_index(vm, index))
		{
			vm_put_pc_move(vm, p->pc, ins->size, ins);
			p->pc = vm_pc(vm, p->pc + ins->size);
			return ;
		}
		p->registre[index] = value;
	}
	else if (ins->args[1].type == ind_arg)
	{
		offset = ins->args[1].value % vm->gconfig.idx_mod;
		pc = vm_pc(vm, p->pc + offset);
		write_int(vm, &pc, value);
	}
	vm_put_instruction(vm, p, ins);
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void	vm_handler_opcode_ldi(t_vm *vm, t_process *p, t_instruction *ins)
{
	int	pc;
	int	index;
	int	addr;
	int	offset;
	int	err;

	index = ins->args[2].value;
	if (check_reg_index(vm, index))
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	addr = access_arg_value(ins->args, vm, p, &err);
	if (err)
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	offset = access_arg_value(ins->args + 1, vm, p, &err);
	if (err)
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	pc = vm_pc(vm, p->pc + ((addr + offset) % vm->gconfig.idx_mod));
	p->registre[index] = read_int(vm, &pc);
	vm_put_instruction(vm, p, ins);
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void				vm_handler_opcode_sti(t_vm *vm, t_process *p, t_instruction *ins)
{
	int	pc;
	int	index;
	int	addr;
	int	offset;
	int	value;
	int	err;

	index = ins->args[0].value;
	if (check_reg_index(vm, index))
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	value = p->registre[index];
	addr = access_arg_value(ins->args + 1, vm, p, &err);
	if (err)
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	offset = access_arg_value(ins->args + 2, vm, p, &err);
	if (err)
	{
		vm_put_pc_move(vm, p->pc, ins->size, ins);
		p->pc = vm_pc(vm, p->pc + ins->size);
		return ;
	}
	pc = vm_pc(vm, p->pc + ((addr + offset) % vm->gconfig.idx_mod));
	write_int(vm, &pc, value);
	vm_put_instruction(vm, p, ins);
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}

void	vm_handler_opcode_fork(t_vm *vm, t_process *p, t_instruction *ins)
{
	int				offset;
	int				pc;

	offset = ins->args[0].value % vm->gconfig.mem_size;
	pc = vm_pc(vm, p->pc + offset);
	vm_new_fprocess(vm, pc, p);
	vm_put_instruction(vm, p, ins);
	vm_put_pc_move(vm, p->pc, ins->size, ins);
	p->pc = vm_pc(vm, p->pc + ins->size);
}
