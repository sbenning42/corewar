/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_declare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:50:11 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/13 19:24:08 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_declare_live(t_vm *vm)
{
	ft_printf("Le joueur %d(%s) est en vie !\n",\
		vm->config.last_live_id, vm_get_player_name(vm, vm->config.last_live_id));
}

void	vm_declare_win(t_vm *vm)
{
	vm_put_players(vm);
	ft_printf("Le joueur %d(%s) a gagné !\n",\
		vm->config.last_live_id, vm_get_player_name(vm, vm->config.last_live_id));
}

void	vm_declare_cycle(t_vm *vm)
{
	ft_printf("It is now cycle %u\n", vm->config.cycle);
}
