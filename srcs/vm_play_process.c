/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_play_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:20:49 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/14 11:01:28 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void				vm_handler_opcode_error(t_vm *vm, t_process *process)
{
	(void)vm;
	(void)process;
	process->pc += 1;
	if (process->pc > (vm->memory + vm->gconfig.mem_size))
		process->pc = vm->memory;
}

static t_vm_opcode_h	g_opcode_handler[] = {\
	{0x1, vm_handler_opcode_live},\
	{0x2, vm_handler_opcode_ld},\
	{0x3, vm_handler_opcode_st},\
	{0x4, vm_handler_opcode_add},\
	{0x5, vm_handler_opcode_sub},\
	{0x6, vm_handler_opcode_and},\
	{0x7, vm_handler_opcode_or},\
	{0x8, vm_handler_opcode_xor},\
	{0x9, vm_handler_opcode_zjmp},\
	{0xa, vm_handler_opcode_ldi},\
	{0xb, vm_handler_opcode_sti},\
	{0xc, vm_handler_opcode_fork},\
	{0xd, vm_handler_opcode_lld},\
	{0xe, vm_handler_opcode_lldi},\
	{0xf, vm_handler_opcode_lfork},\
	{0x10, vm_handler_opcode_aff}\
};

static void				(*dispatch(unsigned char op))(t_vm *, t_process *)
{
	size_t				i;

	i = 0;
	while (i < TABSIZE(g_opcode_handler))
	{
		if (g_opcode_handler[i].opcode == op)
			return (g_opcode_handler[i].func);
		++i;
	}
	return (vm_handler_opcode_error);
}

static void				vm_play_process_i(t_vm *vm, t_process *process)
{
	process->live += 1;
	if (process->timer > 1)
	{
		process->timer -= 1;
		return ;
	}
	dispatch(*process->pc)(vm, process);
}

void					vm_play_process(t_vm *vm)
{
	t_list				*l;

	l = vm->process;
	while (l)
	{
		vm_play_process_i(vm, (t_process *)l->content);
		l = l->next;
	}
}
