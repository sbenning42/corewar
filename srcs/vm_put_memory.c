/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_put_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 08:45:42 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/20 17:42:22 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

# define ABS(X) (X < 0 ? -X : X)

void				vm_put_pc_move(t_vm *vm, int pc_start, int offset, t_instruction *ins)
{
	int				i;

	if (!ISBIT(vm->config.verb, VM_PC_VERB))
		return ;
	ft_printf("ADV %d (0x%04x -> 0x%04x) ", offset, pc_start, vm_pc(vm, pc_start + offset));
	//ft_printf("ADV %d (0x%04x -> 0x%04x [%hhx]) ", offset, pc_start, vm_pc(vm, pc_start + offset), bin_access(vm, pc_start + offset));
	i = -1;
	while (++i < ins->size)
	{
		ft_printf("%02x ", bin_access(vm, pc_start + i));
	}
	ft_printf("\n");
}

void				vm_put_player(t_list *l)
{
	t_player		*player;

	player = (t_player *)l->content;
	ft_printf("* Player %d, weighing %zu bytes, \"%s\" (\"%s\") !\n",\
			ABS(player->id),\
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
//	if (vm->color[i])
//		ft_printf("%s", vm->color[i]);
	if (!o)
		ft_printf("%02x ", o);
	else
		ft_printf("%02x ", o);
//	if (vm->color[i])
//		ft_printf("{eoc}");
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
	stop = vm->gconfig.mem_size / 64;
	while (i < stop)
	{
		ft_printf("0x%04x : ", i * 64);
		vm_put_64(vm, i * 64);
		++i;
	}
}
