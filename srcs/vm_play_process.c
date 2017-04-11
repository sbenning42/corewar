/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_play_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:20:49 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/10 14:56:07 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

typedef void		(*t_ins_reader)(t_process *);

extern t_op			g_op[];

void				noop_op_f(t_process *p)
{
    p->pc += 1;
    if (p->pc > p->player->pc + VM_A_CONFIG.max_player_size)
        p->pc = p->player->pc;
}

void				fill_instruction_wo_ocp(t_process *p)
{
	p->instruction->code = ft_memalloc(p->instruction->size);
	if (!p->instruction->code)
		vm_fatal(VM_EMALLOC);
	ft_memcpy(p->instruction->code, p->pc, p->instruction->size);
	p->instruction->args = p->instruction->code + 1;
//	p->timer += p->instruction->op->cycle;
}

size_t				get_args_size(t_process *p)
{
	size_t			size;
	unsigned char	ocp;
	unsigned char	mask;
	unsigned char	arg;

	size = 0;
	ocp = *(unsigned char *)(p->pc + 1);
    p->instruction->ocp = ocp;
	mask = 0xc0;
	while (ocp)
	{
		arg = ocp & mask;
		if (arg == 0x40)
            size += 1;
        else if (arg == 0x80)
            size += p->instruction->op->label_size;
        else if (arg == 0xc0)
            size += 2;
		ocp <<= 0x2;
	}
    return (size);
}

void				fill_instruction(t_process *p)
{
	p->instruction->size = 2 + get_args_size(p);
	p->instruction->code = ft_memalloc(p->instruction->size);
	if (!p->instruction->code)
		vm_fatal(VM_EMALLOC);
	ft_memcpy(p->instruction->code, p->pc, p->instruction->size);
	p->instruction->args = p->instruction->code + 2;
//	p->timer += p->instruction->op->cycle;
}

void				live_op_f(t_process *p)
{
	p->instruction->op = g_op;
	p->instruction->size = p->instruction->op->label_size + 1;
	fill_instruction_wo_ocp(p);
}

void				ld_op_f(t_process *p)
{
	p->instruction->op = g_op + 1;
    fill_instruction(p);
}

void				st_op_f(t_process *p)
{
	p->instruction->op = g_op + 2;
    fill_instruction(p);
}

void				add_op_f(t_process *p)
{
	p->instruction->op = g_op + 3;
    fill_instruction(p);
}

void				sub_op_f(t_process *p)
{
	p->instruction->op = g_op + 4;
    fill_instruction(p);
}

void				and_op_f(t_process *p)
{
	p->instruction->op = g_op + 5;
    fill_instruction(p);
}

void				or_op_f(t_process *p)
{
	p->instruction->op = g_op + 6;
    fill_instruction(p);
}

void				xor_op_f(t_process *p)
{
	p->instruction->op = g_op + 7;
    fill_instruction(p);
}

void				zjmp_op_f(t_process *p)
{
	p->instruction->op = g_op + 8;
	p->instruction->size = p->instruction->op->label_size + 1;
	fill_instruction_wo_ocp(p);
}

void				ldi_op_f(t_process *p)
{
	p->instruction->op = g_op + 9;
    fill_instruction(p);
}

void				sti_op_f(t_process *p)
{
	p->instruction->op = g_op + 10;
    fill_instruction(p);
}

void				fork_op_f(t_process *p)
{
	p->instruction->op = g_op + 11;
	p->instruction->size = p->instruction->op->label_size + 1;
	fill_instruction_wo_ocp(p);
}

void				lld_op_f(t_process *p)
{
	p->instruction->op = g_op + 12;
    fill_instruction(p);
}

void				lldi_op_f(t_process *p)
{
	p->instruction->op = g_op + 13;
    fill_instruction(p);
}

void				lfork_op_f(t_process *p)
{	

	p->instruction->op = g_op + 14;
	p->instruction->size = p->instruction->op->label_size + 1;
	fill_instruction_wo_ocp(p);
}

void				aff_op_f(t_process *p)
{
	p->instruction->op = g_op + 15;
    fill_instruction(p);
}

static t_ins_reader	g_op_f[] = {\
	noop_op_f,\
	live_op_f,\
	ld_op_f,\
	st_op_f,\
	add_op_f,\
	sub_op_f,\
	and_op_f,\
	or_op_f,\
	xor_op_f,\
	zjmp_op_f,\
	ldi_op_f,\
	sti_op_f,\
	fork_op_f,\
	lld_op_f,\
	lldi_op_f,\
	lfork_op_f,\
	aff_op_f\
};

static t_ins_reader	dispatch(void *pc)
{
	unsigned char	opcode;
	t_op			*op;

	opcode = *(unsigned char *)pc;
	op = g_op;
	while (op->opcode)
	{
		if (op->opcode == opcode)
			return (g_op_f[opcode]);
		++op;
	}
	return (noop_op_f);
}

void				vm_read_instruction(t_process *p)
{
	p->instruction = ft_memalloc(sizeof(t_instruction));
	if (!p->instruction)
		vm_fatal(VM_EMALLOC);
	dispatch(p->pc)(p);
}

void			vm_play_instruction(t_process *p)
{
    if (p->last_instruction)
        free(p->last_instruction);
	p->last_instruction = p->instruction->code;
    p->size_instruction = p->instruction->size;
    vv_msg("TODO: Actually play instruction in vm_play_process");
    p->pc += p->instruction->size;
    if (p->pc > p->player->pc + VM_A_CONFIG.max_player_size)
        p->pc = p->player->pc;
    vv_msg("TODO: Use cbuff to circular handle pc moving. . .");
    vm_print_memory(p->last_instruction, p->size_instruction, p->player->color, 1);
	free(p->instruction);
	p->instruction = NULL;
}

void			vm_play_process(t_list *l)
{
	t_process	*p;

	p = l->content;
	if (p->timer > 0)
    {
	    p->timer -= 1;
		return ;
    }
    else if (p->instruction)
		vm_play_instruction(p);
	vm_read_instruction(p);
}
