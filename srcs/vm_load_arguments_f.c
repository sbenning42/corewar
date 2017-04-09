#include "vm.h"

void        arg_error_f(char *value)
{
    vv_enter("arg_error_f");
    ft_fprintf(2, "%s: Can't understand parametre: %s\n",\
            proginfo()->name, value);
    vv_quit("arg_error_f");
}

void        arg_dump_f(char *value)
{
    t_lexem *l;
    int     n;

    vv_enter("arg_dump_f");
    l = ft_get_arg();
    if (l && l->id == VM_ARG_PARAM && (n = ft_atoi(l->value)) > 0)
        (&VM_A_CONFIG)->dump = n;
    else
        vm_fatal((l ? VM_EUSAGE : VM_EMALLOC));
    lexem_del(&l);
    (void)value;
    vv_quit("arg_dump_f");
}

void        arg_pnum_f(char *value)
{
    t_lexem *l;
    int     n;

    vv_enter("arg_pnum_f");
    l = ft_get_arg();
    if (l && l->id == VM_ARG_PARAM && (n = ft_atoi(l->value)) >= 0)
    {
        lexem_del(&l);
        l = ft_get_arg();
        if (l && l->id == VM_ARG_PARAM)
            vm_create_player(l->value, n);
        else
            vm_fatal((l ? VM_EUSAGE : VM_EMALLOC));
    }
    else
        vm_fatal((l ? VM_EUSAGE : VM_EMALLOC));
    lexem_del(&l);
    (void)value;
    vv_quit("arg_pnum_f");
}

void        arg_oopt_f(char *value)
{
    vv_enter("arg_oopt_f");
    (void)value;
    vv_quit("arg_oopt_f");
}

void        arg_param_f(char *value)
{
    vv_enter("arg_param_f");
    vm_create_player(value, -1);
    vv_quit("arg_param_f");
}
