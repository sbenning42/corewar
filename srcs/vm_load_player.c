#include "vm.h"

static char     *g_color[] = {\
    "{blue}",\
    "{red}",\
    "{green}",\
    "{yellow}"\
};

static char     *get_unique_color(void)
{
    static int  i;

    return (g_color[i++ % TABSIZE(g_color, char *)]);
}

void            vm_load_player_i(t_list *l)
{
    t_player    *p;
    
    vv_enter("vm_load_player_i");
    p = (t_player *)l->content;
    if (read_binary_file(p->obj_file))
        vm_fatal(42);
    if ((p->obj_file->binary_size > sizeof(header_t) + VM_A_CONFIG.max_player_size)\
            || (p->obj_file->binary_size < sizeof(header_t)))
    {
        vm_error(VM_ENOTEXEC);
        p->id = -1;
        return ;
    }
    ft_memcpy(&p->header, p->obj_file->binary, sizeof(header_t));
    p->header.magic = INT_LITTLE2BIG(p->header.magic);
    p->header.prog_size = INT_LITTLE2BIG(p->header.prog_size);
    close(p->obj_file->fd);
    p->obj_file->fd = -1;
    p->color = get_unique_color();
    (&VM_A_CONFIG)->nb_player += 1;
    vv_quit("vm_load_player_i");
}
