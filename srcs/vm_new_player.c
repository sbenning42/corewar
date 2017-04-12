/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_new_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 15:23:00 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/12 16:28:57 by sbenning         ###   ########.fr       */
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

static int		is_available_id(t_vm *vm, int id)
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

static int		get_id(t_vm *vm, int id)
{
	if (id > 0)
	{
		if (is_available_id(vm, id))
			return (id);
	}
	id = 0;
	while (!is_available_id(vm, ++id))
		;
	return (id);
}

static int		vm_read_header(t_player *p)
{
	size_t		size;

	size = read_binary_file(p->file, (unsigned char *)&p->header, sizeof(header_t));
	if (size < sizeof(header_t))
	{
		ft_fprintf(2, "%s: `%s` too small to be a corewar executable\n",\
				prog_name(), p->file->name);
		close_file(p->file)
		return (-1);
	}
	p->header.magic = INT_LITTLE2BIG(p->header.magic);
	p->header.prog_size = INT_LITTLE2BIG(p->header.prog_size);
	return (0);
}

void			vm_new_player(t_vm *vm, char *name, int id)
{
	t_player	player;
	t_list		*l;
	size_t		size;

	ft_bzero(&player, sizeof(player));
	player.id = get_id(vm, id);
	if (!(player.file = open_file(name, O_RDONLY)))
	{
		ft_fprintf(2, "%s: `%s` File not accessible\n", prog_name(), name);
		return ;
	}
	if (vm_read_header(&player))
		return ;
	size = read_binary_file(player.f, player.binary, player.header.prog_size);
	if (size > vm->gconfig.champ_max_size)
	{
		ft_fprintf(2, "%s: `%s` too big to be a corewar executable\n",\
				prog_name(), name);
		close_file(&player.file)
		return ;
	}
	player.color = get_color();
	if (!(l = ft_lstnew(&player, sizeof(player))))
		vm_fatal(VM_EMALLOC);
	ft_lstadd_back(&vm->player, l);
	close_file(&player.file)
	vm->config.nb_player += 1;
}
