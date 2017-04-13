/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_declare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:50:11 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/13 15:58:27 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_declare_live(t_vm *vm, int id)
{
	ft_printf("Le joueur %d(%s) est en vie !\n",\
			id, vm_get_player_name(vm, id));
	(void)vm;
}
