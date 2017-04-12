/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:17:32 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/12 14:19:19 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				vm_is_player_id(t_vm *vm, int id)
{
	t_list		*l;
	t_player	*p;

	l = vm->player;
	while (l)
	{
		p = (t_player *)l->content;
		if (p->id == id)
			return (1);
		l = l->next;
	}
	return (0);
}
