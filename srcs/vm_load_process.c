#include "vm.h"

static void		vm_new_process(t_vm *vm, unsigned char *pc, int id, char *color)
{
	t_list		*l;
	t_process	process;

	ft_bzero(&process, sizeof(process));
	process.pc = pc;
	process.registre[0] = id;
}

void			vm_load_process(t_vm *vm)
{
	size_t		start;
	size_t		offset;
	t_list		*l;
	t_player	*player;

	start = 0;
	offset = vm->gconfig.mem_size / vm->config.nb_player;
	l = vm->player;
	while (l)
	{
		player = (t_player *)l->content;
		start = vm->memory + offset;
		player->pc = start;
		ft_memcpy(start, player->binary, player->header.prog_size);
		vm_new_process(vm, start, player->id, player->color);
		l = l->next;
	}
}
