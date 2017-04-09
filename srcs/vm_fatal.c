#include "vm.h"

static t_efatal         g_fatal[] = {\
    {VM_EMALLOC, VM_MMALLOC},\
    {VM_ENOTEXEC, VM_MNOTEXEC},\
    {VM_EPNUSED, VM_MPNUSED},\
    {VM_ENOTACCESS, VM_MNOTACCESS},\
    {VM_EUSAGE, VM_MUSAGE},\
    {0, NULL}\
};

int                     vm_error(int error)
{
    t_efatal            *f;

    vv_enter("vm_error");
    f = g_fatal;
    while (f->error)
    {
        if (f->error == error)
        {
            ft_fprintf(2, "%s: {red}%s{eoc}\n", proginfo()->name, f->message);
            return (error);
        }
        ++f;
    }
    ft_fprintf(2, "%s: {red}%s{eoc}\n", proginfo()->name, "Unknow error");
    vv_quit("vm_error");
    return (error);
}

void                    vm_fatal(int fatal)
{
    vv_enter("vm_fatal");
    vm_error(fatal);
    exit(1);
}
