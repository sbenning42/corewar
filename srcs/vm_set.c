/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:32:18 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/20 16:01:06 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_set_timer(t_vm *vm, t_process *p)
{
	int		i;
	unsigned char	opcode;

	opcode = bin_access(vm, p->pc);
	i = -1;
	while (g_op[++i].opcode)
	{
		if (opcode == g_op[i].opcode)
		{
			p->opcode = opcode;
			p->timer = g_op[i].cycle;
			return ;
		}
	}
	p->opcode = 0;
	p->timer = 0;
}
