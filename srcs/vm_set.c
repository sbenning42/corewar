/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:32:18 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/20 11:52:30 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_set_timer(t_vm *vm, t_process *p)
{
	int		i;

	i = -1;
	while (g_op[++i].opcode)
	{
		if (vm->memory[p->pc] == g_op[i].opcode)
		{
			p->timer = g_op[i].cycle;
			p->opcode = g_op[i].opcode;
			return ;
		}
	}
	p->timer = 0;
	p->opcode = 0;
}
