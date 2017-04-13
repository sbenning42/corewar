/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:54:06 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/13 15:59:09 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					vm_get_direct_int_arg(unsigned char *pc)
{
	int				arg;

	ft_memcpy(&arg, pc, sizeof(int));
	return (arg);
}

short				vm_get_direct_short_arg(unsigned char *pc)
{
	short			arg;

	ft_memcpy(&arg, pc, sizeof(short));
	return (arg);
}

char				*vm_get_player_name(t_vm *vm, int id)
{
	t_list			*l;

	l = vm->player;
	while (l)
	{
		if (id == ((t_player *)l->content)->id)
			return (((t_player *)l->content)->header.prog_name);
		l = l->next;
	}
	return ("Not a valid player ID");
}
