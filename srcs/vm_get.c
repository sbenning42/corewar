/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:54:06 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/14 12:22:37 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int					vm_get_direct_int_arg(unsigned char *pc)
{
	int				arg;

	ft_memcpy(&arg, pc, 4);
	return (INT_LITTLE2BIG(arg));
}

short				vm_get_direct_short_arg(unsigned char *pc)
{
	short			arg;

	ft_memcpy(&arg, pc, 2);
	return (SHORT_LITTLE2BIG(arg));
}

unsigned char		vm_get_register_arg(unsigned char *pc)
{
	return (*pc - 1);
}

int					vm_get_multi_arg(unsigned char *pc, unsigned char ocp, int *size, int dsize)
{
	unsigned char	mask;

	mask = 0xc0;
	ocp &= mask;
	if (ocp == 0x40)
	{
		*size = 1;
		return ((int)vm_get_register_arg(pc));
	}
	if (ocp == 0x80)
	{
		*size = dsize;
		if (dsize == 4)
			return (vm_get_direct_int_arg(pc));
		else
			return ((int)vm_get_direct_short_arg(pc));
	}
	if (ocp == 0xc0)
	{
		*size = 2;
		return ((int)vm_get_direct_short_arg(pc));
	}
	*size = 0;
	return (0);
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
