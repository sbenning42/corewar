/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handler_opcode_third_set.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:56:52 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/14 15:43:29 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_handler_opcode_ld(t_vm *vm, t_process *p)
{
	unsigned char	*pc;
	unsigned char	ocp;
	int				arg;
	int				size;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 1;
	ocp = *pc;
	pc += 1;
	arg = vm_get_multi_arg(pc, ocp, &size, 4);
	pc += size;
	p->registre[vm_get_register_arg(pc)] = arg;
	pc += 1;
	if (!arg)
		p->carry = 1;
	else
		p->carry = 0;
	p->pc += (pc - p->pc);
	vm_set_timer(p);
}

void	vm_handler_opcode_st(t_vm *vm, t_process *p)
{
	unsigned char	*pc;
	unsigned char	ocp;
	int				val;
	int				reg;
	int				arg;
	int				size;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 1;
	ocp = *pc;
	pc += 1;
	reg = vm_get_register_arg(pc);
	pc += 1;
	ocp <<= 0x02;
	arg = vm_get_multi_arg(pc, ocp, &size, 2);
	pc += size;
	if (size == 1)
		p->registre[arg] = p->registre[reg];
	else
	{
		if (arg < 0)
		{
			arg *= -1;
			arg = arg % vm->gconfig.idx_mod;
			arg *= -1;
		}
		else
			arg = arg % vm->gconfig.idx_mod;
		val = p->registre[reg];
		val = INT_LITTLE2BIG(val);
		ft_memcpy(p->pc + arg, &val, 4);
	}
	p->pc += (pc - p->pc);
	vm_set_timer(p);
}

void	vm_handler_opcode_ldi(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}

void				vm_handler_opcode_sti(t_vm *vm, t_process *p)
{
	unsigned char	*pc;
	unsigned char	ocp;
	int				val;
	int				arg;
	int				size;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 1;
	ocp = *pc;
	pc += 1;
	val = p->registre[vm_get_register_arg(pc)];
	pc += 1;
	ocp <<= 0x2;
	arg = vm_get_multi_arg(pc, ocp, &size, 2);
	pc += size;
	ocp <<= 0x2;
	arg += vm_get_multi_arg(pc, ocp, &size, 2);
	pc += size;
	val = INT_LITTLE2BIG(val);
	if (arg < 0)
	{
		arg *= -1;
		arg = arg % vm->gconfig.idx_mod;
		arg *= -1;
	}
	else
		arg = arg % vm->gconfig.idx_mod;
	ft_memcpy(p->pc + arg, &val, sizeof(int));
	p->pc += (pc - p->pc);
	vm_set_timer(p);
}

void	vm_handler_opcode_fork(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
}
