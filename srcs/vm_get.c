/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 12:54:06 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/11 12:57:09 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char			*vm_get_player_name(int id)
{
	t_list		*l;
	t_player	*p;

	l = VM_A_PLAYER;
	while (l)
	{
		p = (t_player *)l->content;
		if (p->id == id)
			return (p->header.prog_name);
		l = l->next;
	}
	return ("Unknow player");
}
