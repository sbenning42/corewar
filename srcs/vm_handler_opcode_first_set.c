/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_handler_opcode_first_set.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 14:36:06 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/18 13:56:44 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_handler_opcode_live(t_vm *vm, t_process *p)
{
	t_vm_arg	args;
	int			id;

	p->live = 0;
	vm->config.nb_live += 1;
	vm_read_args(vm, g_op, p, &args);
	id = args.args[0].val.int_v;
	if (!is_available_id(vm, id))
	{
		vm->config.last_live_id = id;
		if (ISBIT(vm->config.verb, VM_LIVE_VERB))
			vm_declare_live(vm, p->id);
	}
	vm_inc_pc(vm, &p->pc, 1 + args.size);
	vm_set_timer(vm, p);
}

void	vm_handler_opcode_add(t_vm *vm, t_process *p)
{
	t_vm_arg	args;
	int			i_res;
	int			i_op1;
	int			i_op2;

	vm_read_args(vm, g_op + OP_ADD_I, p, &args);
	i_op1 = (int)args.args[0].val.index;
	i_op2 = (int)args.args[1].val.index;
	i_res = (int)args.args[2].val.index;
	p->registre[i_res] = p->registre[i_op1] + p->registre[i_op2];
	if (!p->registre[i_res])
		p->carry = 1;
	else
		p->carry = 0;
	vm_inc_pc(vm, &p->pc, 1 + args.size);
	vm_set_timer(vm, p);
}

void	vm_handler_opcode_sub(t_vm *vm, t_process *p)
{
	t_vm_arg	args;
	int			i_res;
	int			i_op1;
	int			i_op2;

	vm_read_args(vm, g_op + OP_SUB_I, p, &args);
	i_op1 = (int)args.args[0].val.index;
	i_op2 = (int)args.args[1].val.index;
	i_res = (int)args.args[2].val.index;
	p->registre[i_res] = p->registre[i_op1] - p->registre[i_op2];
	if (!p->registre[i_res])
		p->carry = 1;
	else
		p->carry = 0;
	vm_inc_pc(vm, &p->pc, 1 + args.size);
	vm_set_timer(vm, p);
}

void	vm_handler_opcode_aff(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
/*	unsigned char	*pc;

	vm_put_instruction(vm, p);
	pc = p->pc;
	pc += 2;
	if (vm->config.aff > 0)
		ft_printf("%c", p->registre[vm_get_register_arg(pc)] % 256);
	p->pc += 3;
	vm_set_timer(p);
*/}

void		vm_handler_opcode_zjmp(t_vm *vm, t_process *p)
{
	(void)vm;
	(void)p;
/*	unsigned char	*pc;
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
*/}
