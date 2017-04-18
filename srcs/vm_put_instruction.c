/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_put_instruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 13:02:31 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/18 13:22:04 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_put_instruction(t_vm *vm, t_process *p)
{
	if (ISBIT(vm->config.verb, VM_OP_VERB))
		ft_printf("P\t%2d | %s\n", p->id, g_op[vm->memory[p->pc - 1]].id);
}
