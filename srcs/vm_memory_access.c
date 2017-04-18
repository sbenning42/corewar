/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_memory_acces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 12:27:36 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/18 13:44:04 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

unsigned char				vm_read_byte(t_vm *vm, int pc)
{
	if (pc < 0 || pc >= vm->gconfig.mem_size)
	{
		ft_printf("SIGV out of range\n");
		vm_fatal(42);
	}
	return (vm->memory[pc]);
}

void						vm_inc_pc(t_vm *vm, int *pc, int offset)
{
	*pc = (*pc + offset) % vm->gconfig.mem_size;
}

void						vm_dec_pc(t_vm *vm, int *pc, int offset)
{
	int						i;

	i = 1;
	while (--i > offset)
	{
		*pc -= 1;
		if (*pc < 0)
			*pc = vm->gconfig.mem_size;
	}
}

unsigned char				vm_consume_byte(t_vm *vm, int *pc)
{
	unsigned char			byte;

	byte = vm_read_byte(vm, *pc);
	vm_inc_pc(vm, pc, 1);
	return (byte);
}

static unsigned char		get_ocp(t_op *op)
{
	unsigned int			i;
	unsigned char			ocp_a;
	unsigned char			ocp;

	ocp = 0;
	i = 0;
	while (i < op->nb_arg)
	{
		ocp_a = (op->args_type[i] << 0x6) >> (i * 0x2);
		ocp |= ocp_a;
		++i;
	}
	return (ocp);
}

void						vm_read_reg(t_vm *vm, t_op *op, int *pc, t_vm_arg *vmargs)
{
	vmargs->args[vmargs->nb_arg].type = vm_at_index;
	vmargs->args[vmargs->nb_arg].val.index = (char)vm_consume_byte(vm, pc);
	vmargs->nb_arg += 1;
	vmargs->size += 1;
	(void)op;
}

void						vm_read_dir(t_vm *vm, t_op *op, int *pc, t_vm_arg *vmargs)
{
	short					sval;
	int						ival;
	unsigned char			tab[4];

	ft_bzero(tab, sizeof(unsigned char) * 4);
	if (op->label_size == 2)
	{
		vmargs->args[vmargs->nb_arg].type = vm_at_sh_dir;
		tab[0] = vm_consume_byte(vm, pc);
		tab[1] = vm_consume_byte(vm, pc);
		ft_memcpy(&sval, tab, 2);
		sval = SHORT_LITTLE2BIG(sval);
		vmargs->args[vmargs->nb_arg].val.short_v = sval;
		vmargs->size += 2;
	}
	else
	{
		vmargs->args[vmargs->nb_arg].type = vm_at_sh_dir;
		tab[0] = vm_consume_byte(vm, pc);
		tab[1] = vm_consume_byte(vm, pc);
		tab[2] = vm_consume_byte(vm, pc);
		tab[3] = vm_consume_byte(vm, pc);
		ft_memcpy(&ival, tab, 4);
		ival = INT_LITTLE2BIG(ival);
		vmargs->args[vmargs->nb_arg].val.int_v = ival;
		vmargs->size += 4;
	}
	vmargs->nb_arg += 1;
}

void						vm_read_ind(t_vm *vm, t_op *op, int *pc, t_vm_arg *vmargs)
{
	unsigned char			tab[2];
	short					val;

	vmargs->args[vmargs->nb_arg].type = vm_at_ind;
	tab[0] = vm_consume_byte(vm, pc);
	tab[1] = vm_consume_byte(vm, pc);
	ft_memcpy(&val, tab, 2);
	val = SHORT_LITTLE2BIG(val);
	vmargs->args[vmargs->nb_arg].val.short_v = val;
	vmargs->nb_arg += 1;
	vmargs->size += 2;
	(void)op;
}

void						vm_read_error(t_vm *vm, t_op *op, int *pc, t_vm_arg *vmargs)
{
	ft_printf("Wrong ocp\n");
	vm_fatal(-42);
	(void)vm;
	(void)op;
	(void)pc;
	(void)vmargs;
}

static void					(*dispatch(unsigned char ocp))(t_vm *, t_op *, int *, t_vm_arg *)
{
	if (ocp == T_REG)
		return (vm_read_reg);
	else if (ocp == T_DIR)
		return (vm_read_dir);
	else if (ocp == T_IND)
		return (vm_read_ind);
	ft_printf("ocp = %x\n", ocp);
	return (vm_read_error);
}

void						vm_read_args(t_vm *vm, t_op *op, t_process *p, t_vm_arg *vmargs)
{
	int						pc;
	unsigned char			ocp;
	unsigned char			ocp_a;

	ft_bzero(vmargs, sizeof(t_vm_arg));
	vmargs->size = op->ocp;
	pc = p->pc + 1;
	if (op->ocp)
		ocp = vm_consume_byte(vm, &pc);
	else
		ocp = get_ocp(op);
	while (ocp)
	{
		ocp_a = ((ocp & 0xc0) >> 0x6);
		dispatch(ocp_a)(vm, op, &pc, vmargs);
		ocp <<= 0x2;
	}
}
