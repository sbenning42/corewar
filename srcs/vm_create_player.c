#include "vm.h"

static int      vm_player_is_id(int id)
{
    t_player    *p;
    t_list      *l;

    l = VM_A_PLAYER;
    while (l)
    {
        p = (t_player *)l->content;
        if (p->id == id)
            return (1);
        l = l->next;
    }
    return (0);
}

static int      vm_player_get_id(void)
{
    int         id;

    id = 1;
    while (vm_player_is_id(id))
        ++id;
    return (id);
}

void            vm_create_player(char *file_name, int id)
{
    t_player    p;
    t_list      *l;

    vv_enter("vm_create_player");
    if (id < 0)
        id = vm_player_get_id();
    if (vm_player_is_id(id))
    {
        vm_error(VM_EPNUSED);
        id = vm_player_get_id();
    }
    ft_bzero(&p, sizeof(t_player));
    p.id = id;
    p.obj_file = open_file(file_name, O_RDONLY);
    if (!p.obj_file)
    {
        vm_error(VM_ENOTACCESS);
        return ;
    }
    if (!(l = ft_lstnew(&p, sizeof(t_player))))
        vm_fatal(VM_EMALLOC);
    ft_lstadd_back(&VM_A_PLAYER, l);
    vv_quit("vm_create_player");
}
