/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_put_instruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 13:02:31 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/19 16:03:34 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char	*strtype(t_e_insarg t)
{
	if (t == reg_arg)
		return ("Registre");
	else if (t == dir_arg)
		return ("Direct");
	else if (t == ind_arg)
		return ("Indirect");
	return ("UKN");
}

void		vm_put_instruction(t_vm *vm, t_process *p, t_instruction *ins)
{
	char	buff[2048];
	char	i_buff[512];
	int	i;

	if (!ISBIT(vm->config.verb, VM_OP_VERB))
		return ;
	buff[0] = 0;
	i = -1;
	while (++i < ins->nb_arg)
	{
		ft_sprintf(i_buff, "%s %d%s", strtype(ins->args[i].type), ins->args[i].value, (i + 1 == ins->nb_arg ? "" : ", "));
		ft_strcat(buff, i_buff);
	}
	ft_printf("P\t%2d | %s (%s)\n", p->id, g_op[ins->op - 1].id, buff);
}
