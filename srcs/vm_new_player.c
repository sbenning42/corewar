/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_new_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:23:00 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/19 16:25:52 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static char		*get_color(void)
{
	static char	*color[] = {\
		"\033[38;2;0;0;255m",\
		"\033[38;2;255;0;0m",\
		"\033[38;2;0;255;0m",\
		"\033[38;2;255;255;0m"\
	};
	static int	i = -1;

	return (color[(++i % TABSIZE(color))]);
}

int				is_available_id(t_vm *vm, long int id)
{
	t_list		*l;

	l = vm->player;
	while (l)
	{
		if (((t_player *)l->content)->id == id)
			return (0);
		l = l->next;
	}
	return (1);
}

static long int	get_id(t_vm *vm, long int id)
{
	while (!is_available_id(vm, id))
		--id;
	return (id);
}

static void		vm_load_player_file(t_player *p)
{
	size_t		hsize;
	size_t		size;

	hsize = sizeof(header_t);
	size = hsize;
	ft_memcpy(&p->header, p->file->binary, size);
	p->header.magic = INT_LITTLE2BIG(p->header.magic);
	p->header.prog_size = INT_LITTLE2BIG(p->header.prog_size);
	size = p->file->binary_size - hsize;
	ft_memcpy(p->binary, p->file->binary + hsize, size);
	p->binary_size = size;
}

static int		vm_check_champ_size(t_vm *vm, t_player *player)
{
	size_t		hsize;

	hsize = sizeof(header_t);
	if ((player->file->binary_size < hsize)\
			|| (player->file->binary_size > hsize + vm->gconfig.champ_max_size))
	{
		vm_error_notcorewar(player->file->name);
		return (1);
	}
	return (0);
}

void			vm_new_player(t_vm *vm, char *name, long int id)
{
	t_player	player;
	t_list		*l;

	ft_bzero(&player, sizeof(t_player));
	if (vm->config.nb_player >= vm->gconfig.max_player)
		return ;
	if (!(player.file = open_file(name, O_RDONLY)))
	{
		vm_error_notaccess(name);
		return ;
	}
	if (read_binary_file(player.file))
		vm_fatal(VM_EMALLOC);
	if (vm_check_champ_size(vm, &player))
	{
		close_file(&player.file);
		return ;
	}
	vm_load_player_file(&player);
	close_file(&player.file);
	player.id = get_id(vm, id);
	player.color = get_color();
	if (!(l = ft_lstnew(&player, sizeof(t_player))))
		vm_fatal(VM_EMALLOC);
	ft_lstadd_back(&vm->player, l);
	vm->config.nb_player += 1;
}
