/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_put_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 08:45:42 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/13 11:04:28 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				vm_put_player(t_list *l)
{
	t_player		*player;

	player = (t_player *)l->content;
	ft_printf("* Player %d, weighing %zu bytes, \"%s\" (\"%s\") !\n",\
			player->id,\
			player->header.prog_size,\
			player->header.prog_name,\
			player->header.comment);
}

void				vm_put_players(t_vm *vm)
{
	if (vm->config.nb_player < 1)
		return ;
	ft_printf("Introducing contestants...\n");
	ft_lstiter(vm->player, vm_put_player);
}

void				vm_put_byte(t_vm *vm, size_t i)
{
	unsigned char	o;

	o = vm->memory[i];
	if (!o)
		ft_printf("%02x ", o);
	else
		ft_printf("{gr}%02x{eoc} ", o);
}

void				vm_put_64(t_vm *vm, size_t start)
{
	size_t			i;

	i = 0;
	while (i < 64)
	{
		vm_put_byte(vm, start + i);
		++i;
	}
	ft_printf("\n");
}

void				vm_put_memory(t_vm *vm)
{
	size_t			stop;
	size_t			i;

	i = 0;
	vm_put_players(vm);
	stop = vm->gconfig.mem_size / 64;
	while (i < stop)
	{
		ft_printf("0x%04x : ", i * 64);
		vm_put_64(vm, i * 64);
		++i;
	}
}
