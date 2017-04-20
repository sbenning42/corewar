/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 15:14:03 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/20 17:46:40 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				ft_endian(void)
{
	int			endian;

	endian = 1;
	return (*(char *)&endian);
}

int				ft_intswap(int i)
{
	t_swap		origin;
	t_swap		swap;

	origin.u_int = i;
	swap.u_tab[0] = origin.u_tab[3];
	swap.u_tab[1] = origin.u_tab[2];
	swap.u_tab[2] = origin.u_tab[1];
	swap.u_tab[3] = origin.u_tab[0];
	return (swap.u_int);
}

short			ft_shortswap(short sh)
{
	t_swap		origin;
	t_swap		swap;

	origin.u_short = sh;
	swap.u_tab[0] = origin.u_tab[1];
	swap.u_tab[1] = origin.u_tab[0];
	return (swap.u_short);
}

int				ft_bigint(int i)
{
	return ((ft_endian() ? ft_intswap(i) : i));
}

int				ft_littleint(int i)
{
	return ((ft_endian() ? i : ft_intswap(i)));
}

short			ft_bigshort(short sh)
{
	return ((ft_endian() ? ft_shortswap(sh) : sh));
}

short			ft_littleshort(short sh)
{
	return ((ft_endian() ? sh : ft_shortswap(sh)));
}

int				vm_pc(t_vm *vm, int pc)
{
	return (((pc % vm->gconfig.mem_size) + (pc < 0 ? vm->gconfig.mem_size : 0)));
}

unsigned char	bin_access(t_vm *vm, int pc)
{
	return (vm->memory[vm_pc(vm, pc)]);
}

unsigned char	*bin_access_w(t_vm *vm, int pc)
{
	return (vm->memory + vm_pc(vm, pc));
}

char			bin_char(t_vm *vm, int pc)
{
	return ((char)bin_access(vm, pc));
}

short			bin_short(t_vm *vm, int pc)
{
	t_swap		swap;

	swap.u_tab[0] = bin_access(vm, pc++);
	swap.u_tab[1] = bin_access(vm, pc);
	return (swap.u_short);
}

int				bin_int(t_vm *vm, int pc)
{
	t_swap		swap;

	swap.u_tab[0] = bin_access(vm, pc++);
	swap.u_tab[1] = bin_access(vm, pc++);
	swap.u_tab[2] = bin_access(vm, pc++);
	swap.u_tab[3] = bin_access(vm, pc);
	return (swap.u_int);
}

int				read_int(t_vm *vm, int *pc)
{
	int			i;

	i = ft_bigint(bin_int(vm, *pc));
	*pc = vm_pc(vm, *pc + 4);
	return (i);
}

void			write_int(t_vm *vm, int *pc, int value)
{
	t_swap		swap;
	int			cp_pc;

	cp_pc = *pc;
	swap.u_int = ft_bigint(value);
	*bin_access_w(vm, cp_pc++) = swap.u_tab[0];
	*bin_access_w(vm, cp_pc++) = swap.u_tab[1];
	*bin_access_w(vm, cp_pc++) = swap.u_tab[2];
	*bin_access_w(vm, cp_pc) = swap.u_tab[3];
}

int				read_short(t_vm *vm, int *pc)
{
	short		s;

	s = ft_bigshort(bin_short(vm, *pc));
	*pc = vm_pc(vm, *pc + 2);
	return ((int)s);
}

int				read_char(t_vm *vm, int *pc)
{
	char		c;

	c = bin_char(vm, *pc);
	*pc = vm_pc(vm, *pc + 1);
	return ((int)c);
}

int				fill_reg(t_insarg_i *arg, t_vm *vm, int *pc, int label_size)
{
	arg->type = reg_arg;
	arg->value = read_char(vm, pc);
	return (1);
	(void)label_size;
}

int				fill_ind(t_insarg_i *arg, t_vm *vm, int *pc, int label_size)
{
	arg->type = ind_arg;
	arg->value = read_short(vm, pc);
	return (2);
	(void)label_size;
}

int				fill_dir(t_insarg_i *arg, t_vm *vm, int *pc, int label_size)
{
	arg->type = dir_arg;
	if (label_size == 4)
		arg->value = read_int(vm, pc);
	else
		arg->value = read_short(vm, pc);
	return (label_size);
}

int				fill_null(t_insarg_i *arg, t_vm *vm, int *pc, int label_size)
{
	(void)arg;
	(void)vm;
	(void)pc;
	(void)label_size;
	return (0);
}

static int		(*dispatch(unsigned char ocp))(t_insarg_i *, t_vm *, int *, int)
{
	ocp &= 0xc0;
	if (ocp == 0x40)
		return (fill_reg);
	else if (ocp == 0x80)
		return (fill_dir);
	else if (ocp == 0xc0)
		return (fill_ind);
	return (fill_null);
}

void			fill_args(t_instruction *ins, t_vm *vm, int pc, int label_size)
{
	unsigned char	ocp;

	ins->nb_arg = 0;
	ocp = ins->ocp;
	while (ocp)
	{
		ins->size += dispatch(ocp)\
					 (ins->args + ins->nb_arg,\
					  vm, &pc, label_size);
		ins->nb_arg += 1;
		ocp <<= 0x2;
	}
}

int					get_op_index(unsigned int opcode)
{
	int				i;

	i = -1;
	while (g_op[++i].id)
	{
		if (opcode == g_op[i].opcode)
			return (i);
	}
	return (-1);
}

unsigned char		make_ocp(t_op op)
{
	unsigned int	i;
	unsigned char	ocp;

	i = 0;
	ocp = 0;
	while (i < op.nb_arg)
	{
		ocp |= (op.args_type[i] << 0x6) >> (0x2 * i);
		++i;
	}
	return (ocp);
}

void				vm_read_instruction(t_vm *vm, int pc, t_instruction *ins, unsigned char opcode)
{
	int				op_index;

	ins->pc = pc;
	//ins->op = opcode;
	(void)opcode;
	ins->op = bin_access(vm, pc);
	pc = vm_pc(vm, pc + 1);
	ins->size = 1;
	op_index = get_op_index(ins->op);
	if (op_index < 0)
		return ;
	if (g_op[op_index].ocp)
	{
		ins->ocp = bin_access(vm, pc);
		pc = vm_pc(vm, pc + 1);
		ins->size += 1;
	}
	else
		ins->ocp = make_ocp(g_op[op_index]);
	fill_args(ins, vm, pc, g_op[op_index].label_size);
}

int				check_reg_index(t_vm *vm, int i)
{
	if (i < 1 || i > vm->gconfig.reg_number)
		return (-1);
	return (0);
}

int				access_reg_arg(t_insarg_i *arg, t_process *p, int *err)
{
	if (arg->value < 1 || arg->value > 16)
	{
		*err = 1;
		return (0);
	}
	return (p->registre[arg->value]);
}

int				access_dir_arg(t_insarg_i *arg)
{
	return (arg->value);
}

int				access_ind_arg(t_insarg_i *arg, t_vm *vm, t_process *p)
{
	int			pc;

	pc = vm_pc(vm, p->pc + (arg->value % vm->gconfig.idx_mod));
	return (read_int(vm, &pc));
}

int				access_arg_value(t_insarg_i *arg, t_vm *vm, t_process *p, int *err)
{
	*err = 0;
	if (arg->type == reg_arg)
		return (access_reg_arg(arg, p, err));
	else if (arg->type == dir_arg)
		return (access_dir_arg(arg));
	return (access_ind_arg(arg, vm, p));
}
