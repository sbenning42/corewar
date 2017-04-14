/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handler_opcode_first_set.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:36:06 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/14 15:25:48 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_handler_opcode_live(t_vm *vm, t_process *p)
{
	int	arg;
	unsigned char *pc;

	vm_put_instruction(vm, p);
	pc = p->pc;
	p->live = 0;
	pc += 1;
	arg = vm_get_direct_int_arg(pc);
	pc += 4;
	vm->config.nb_live += 1;
	if (!is_available_id(vm, arg))
	{
		vm->config.last_live_id = arg;
		if (ISBIT(vm->config.verb, VM_LIVE_VERB))
			vm_declare_live(vm, p->id);
	}
	p->pc += 5;
	vm_set_timer(p);
}

void	vm_handler_opcode_add(t_vm *vm, t_process *p)
{
	unsigned char	*pc;
	int				i1;
	int				i2;
	int				ires;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 1;
	i1 = vm_get_register_arg(pc);
	pc += 1;
	i2 = vm_get_register_arg(pc);
	pc += 1;
	ires = vm_get_register_arg(pc);
	pc += 1;
	p->registre[ires] = p->registre[i1] + p->registre[i2];
	if (!p->registre[ires])
		p->carry = 1;
	else
		p->carry = 0;
	p->pc += 4;
	vm_set_timer(p);
}

void	vm_handler_opcode_sub(t_vm *vm, t_process *p)
{
	unsigned char	*pc;
	int				i1;
	int				i2;
	int				ires;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 1;
	i1 = vm_get_register_arg(pc);
	pc += 1;
	i2 = vm_get_register_arg(pc);
	pc += 1;
	ires = vm_get_register_arg(pc);
	pc += 1;
	p->registre[ires] = p->registre[i1] - p->registre[i2];
	if (!p->registre[ires])
		p->carry = 1;
	else
		p->carry = 0;
	p->pc += 4;
	vm_set_timer(p);
}

void	vm_handler_opcode_aff(t_vm *vm, t_process *p)
{
	unsigned char	*pc;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 2;
	if (vm->config.aff > 0)
		ft_printf("%c", p->registre[vm_get_register_arg(pc)] % 256);
	p->pc += 3;
	vm_set_timer(p);
}

void		vm_handler_opcode_zjmp(t_vm *vm, t_process *p)
{
	unsigned char	*pc;
	short			arg;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 1;
	arg = vm_get_direct_short_arg(pc);
	if (arg < 0)
	{
		arg *= -1;
		arg = arg % vm->gconfig.idx_mod;
		arg *= -1;
	}
	else
		arg = arg % vm->gconfig.idx_mod;
	if (p->carry)
		p->pc += arg;
	else
		p->pc += 3;
	vm_set_timer(p);
}
