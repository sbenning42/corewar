/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_player.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 11:35:07 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/11 14:21:12 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					vm_get_arg_type(t_instruction *ins, int i)
{
	unsigned char	ocp;

	ocp = ins->ocp;
	while (i--)
		ocp <<= 0x2;
	return (ocp & 0xc0);
}

void			vm_player_noop(t_process *p)
{
	ft_fprintf(2, "Should not get this ins [%c]\n", *p->instruction->code);
}

void			vm_player_live(t_process *p)
{
	int			arg;

	p->live += 1;
	(&VM_A_CONFIG)->nbr_live_check += 1;
	ft_memcpy(&arg, p->instruction->args, p->instruction->op->label_size);
	arg = INT_LITTLE2BIG(arg);
	(&VM_A_CONFIG)->id_last_live = arg;
	(&VM_A_CONFIG)->name_last_live = vm_get_player_name(arg);
	vm_declare_live();
    p->pc += p->instruction->size;
    if (p->pc > p->player->pc + VM_A_CONFIG.max_player_size)
        p->pc = p->player->pc;
}

void				vm_player_ld(t_process *p)
{
	int				arg_type;
	int				arg;

	arg = 0;
	arg_type = vm_get_arg_type(p->instruction, 0);
//	ft_printf("ARG TYPE : [%02x]\n", arg_type);
	ft_memcpy((void *)(arg_type == 0x80 ? (char *)&arg : ((char *)&arg) + 2), p->instruction->args, (arg_type == 0x80 ? sizeof(int) : sizeof(short)));
	//arg = (arg_type == 0x80 ? INT_LITTLE2BIG(arg) : SHORT_LITTLE2BIG(*(short *)((char *)&arg + 2)));
	ft_printf("LD 1st ARG = [%02x]\n", arg);
    p->pc += p->instruction->size;
    if (p->pc > p->player->pc + VM_A_CONFIG.max_player_size)
        p->pc = p->player->pc;
	(void)p;
}

void			vm_player_st(t_process *p)
{
	(void)p;
}

void			vm_player_add(t_process *p)
{
	(void)p;
}

void			vm_player_sub(t_process *p)
{
	(void)p;
}

void			vm_player_and(t_process *p)
{
	(void)p;
}

void			vm_player_or(t_process *p)
{
	(void)p;
}

void			vm_player_xor(t_process *p)
{
	(void)p;
}

void			vm_player_zjmp(t_process *p)
{
	(void)p;
}

void			vm_player_ldi(t_process *p)
{
	(void)p;
}

void			vm_player_sti(t_process *p)
{
	(void)p;
}

void			vm_player_fork(t_process *p)
{
	(void)p;
}

void			vm_player_lld(t_process *p)
{
	(void)p;
}

void			vm_player_lldi(t_process *p)
{
	(void)p;
}

void			vm_player_lfork(t_process *p)
{
	(void)p;
}

void			vm_player_aff(t_process *p)
{
	(void)p;
}

t_ins_player	g_player[] = {\
	vm_player_noop,\
	vm_player_live,\
	vm_player_ld,\
	vm_player_st,\
	vm_player_add,\
	vm_player_sub,\
	vm_player_and,\
	vm_player_or,\
	vm_player_xor,\
	vm_player_zjmp,\
	vm_player_ldi,\
	vm_player_sti,\
	vm_player_fork,\
	vm_player_lld,\
	vm_player_lldi,\
	vm_player_lfork,\
	vm_player_aff,\
	NULL\
};

t_ins_player	vm_player_dispatch(unsigned int opcode)
{
	int			i;

	i = -1;
	while (g_player[++i])
	{
		if (opcode == (unsigned int)i)
		{
			return (g_player[i]);
		}
	}
	return (vm_player_noop);
}
