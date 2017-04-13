#include "vm.h"

static void			vm_new_process\
						(t_vm *vm, unsigned char *pc, int id, char *color)
{
	t_list			*l;
	t_process		process;

	ft_bzero(&process, sizeof(process));
	process.player_id = id;
	process.color = color;
	process.pc = pc;
	process.registre[0] = id;
	vm_set_timer(&process);
	if (!(l = ft_lstnew(&process, sizeof(process))))
		vm_fatal(VM_EMALLOC);
	ft_lstadd(&vm->process, l);
}

void				vm_load_process(t_vm *vm)
{
	unsigned char	*start;
	size_t			offset;
	t_list			*l;
	t_player		*player;

	if (vm->config.nb_player < 1)
		return ;
	start = vm->memory;
	offset = vm->gconfig.mem_size / vm->config.nb_player;
	l = vm->player;
	while (l)
	{
		player = (t_player *)l->content;
		player->pc = start;
		ft_memcpy(start, player->binary, player->binary_size);
		int i = -1;
		while (++i < (int)player->binary_size)
			vm->color[(start - vm->memory) + i] = player->color;
		vm_new_process(vm, start, player->id, player->color);
		start += offset;
		l = l->next;
	}
}
