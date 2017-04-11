#include "vm.h"

void            vm_dump_header(header_t *h)
{
    ft_printf(VM_HEADER_DUMP,\
            "Magic", h->magic,\
            "Prog Name", h->prog_name,\
            "Prog Size", h->prog_size,\
            "Comment", h->comment);
}

void            vm_dump_player_i(t_list *l)
{
    t_player    *p;

    vv_enter("vm_dump_player");
    ft_printf("\tPlayer:\n");
    p = (t_player *)l->content;
    ft_printf(VM_PLAYER_DUMP,\
            "Id", p->id,\
            "File Name", p->obj_file->name,\
            "Number Live this Check", p->live,\
            "Player Dead", p->dead,\
            "Program address", p->pc,\
            "Player Color", p->color\
            );
    vm_dump_header(&p->header);
    vv_quit("vm_dump_player");
}

void			vm_put_player_i(t_list *l)
{
	t_player	*p;

	p = (t_player *)l->content;
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",\
			p->id, p->header.prog_size, p->header.prog_name, p->header.comment);
}

void		vm_put_players(void)
{
	ft_printf("Introducing contestants...\n");
	ft_lstiter(VM_A_PLAYER, vm_put_player_i);
}




