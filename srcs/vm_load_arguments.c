#include "vm.h"

static t_argd   g_dispatch[] = {\
    {VM_ARG_ERR, arg_error_f},\
    {VM_ARG_DUMP, arg_dump_f},\
    {VM_ARG_PNUM, arg_pnum_f},\
    {VM_ARG_OOPT, arg_oopt_f},\
    {VM_ARG_PARAM, arg_param_f},\
    {0, NULL}\
};

void            unknow_fatal(char *value)
{
    vm_fatal(-42);
    (void)value;
}

t_arg_f         arg_dispatch(int type)
{
    t_argd  *dispatch;

    dispatch = g_dispatch;
    while (dispatch->f)
    {
        if (type == dispatch->type)
            return (dispatch->f);
        ++dispatch;
    }
    return (unknow_fatal);
}
