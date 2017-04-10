/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_play_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:20:49 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/10 14:11:47 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

typedef void		(*t_ins_reader)(t_process *);

extern t_op			g_op[];

void				noop_op_f(t_process *p)
{
	(void)p;
}

void				live_op_f(t_process *p)
{
	p->instruction->op = g_op;
	p->instruction->size = p->instruction->op->label_size + 1;
	p->instruction->code = ft_memalloc(p->instruction->size);
	ft_memcpy(p->instruction->code, p->pc, p->instruction->size);
	if (!p->instruction->code)
		vm_fatal(VM_EMALLOC);
	p->instruction->args = p->instruction->code + 1;
	p->pc += p->instruction->size;
	p->timer += p->instruction->op->cycle;
	ft_print_legit_memory(p->instruction->code, p->instruction->size);
}

void				ld_op_f(t_process *p)
{
	(void)p;
}

void				st_op_f(t_process *p)
{
	(void)p;
}

void				add_op_f(t_process *p)
{
	(void)p;
}

void				sub_op_f(t_process *p)
{
	(void)p;
}

void				and_op_f(t_process *p)
{
	(void)p;
}

void				or_op_f(t_process *p)
{
	(void)p;
}

void				xor_op_f(t_process *p)
{
	(void)p;
}

void				zjmp_op_f(t_process *p)
{
	p->instruction->op = g_op + 8;
	p->instruction->size = p->instruction->op->label_size + 1;
	p->instruction->code = ft_memalloc(p->instruction->size);
	ft_memcpy(p->instruction->code, p->pc, p->instruction->size);
	if (!p->instruction->code)
		vm_fatal(VM_EMALLOC);
	p->instruction->args = p->instruction->code + 1;
	p->pc += p->instruction->size;
	p->timer += p->instruction->op->cycle;
	ft_print_legit_memory(p->instruction->code, p->instruction->size);
}

void				ldi_op_f(t_process *p)
{
	(void)p;
}

void				sti_op_f(t_process *p)
{
	(void)p;
}

void				fork_op_f(t_process *p)
{
	p->instruction->op = g_op + 11;
	p->instruction->size = p->instruction->op->label_size + 1;
	p->instruction->code = ft_memalloc(p->instruction->size);
	ft_memcpy(p->instruction->code, p->pc, p->instruction->size);
	if (!p->instruction->code)
		vm_fatal(VM_EMALLOC);
	p->instruction->args = p->instruction->code + 1;
	p->pc += p->instruction->size;
	p->timer += p->instruction->op->cycle;
	ft_print_legit_memory(p->instruction->code, p->instruction->size);
}

void				lld_op_f(t_process *p)
{
	(void)p;
}

void				lldi_op_f(t_process *p)
{
	(void)p;
}

void				lfork_op_f(t_process *p)
{	
	p->instruction->op = g_op + 14;
	p->instruction->size = p->instruction->op->label_size + 1;
	p->instruction->code = ft_memalloc(p->instruction->size);
	ft_memcpy(p->instruction->code, p->pc, p->instruction->size);
	if (!p->instruction->code)
		vm_fatal(VM_EMALLOC);
	p->instruction->args = p->instruction->code + 1;
	p->pc += p->instruction->size;
	p->timer += p->instruction->op->cycle;
	ft_print_legit_memory(p->instruction->code, p->instruction->size);
}

void				aff_op_f(t_process *p)
{
	(void)p;
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
	ft_printf("DEBUG: [%x]\n", opcode);
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
	free(p->instruction->code);
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
	if (p->instruction)
		vm_play_instruction(p);
	vm_read_instruction(p);
}
