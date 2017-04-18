/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_declare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:50:11 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/18 13:21:16 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_declare_live(t_vm *vm, long int id)
{
	ft_printf("Process %ld, said contestant %d, \"%s\" is alived !\n",\
		id,\
		vm->config.last_live_id,\
		vm_get_player_name(vm, vm->config.last_live_id));
}

void	vm_declare_win(t_vm *vm)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",\
		vm->config.last_live_id,\
		vm_get_player_name(vm, vm->config.last_live_id));
}

void	vm_declare_cycle(t_vm *vm)
{
	ft_printf("It is now cycle %u\n", vm->config.cycle_tot);
}
