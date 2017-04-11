#include "vm.h"

void        vv_enter(char *f)
{
    if (!PI_ISOPT(proginfo()->opt, VM_VVERBOSE_OPT))
        return ;
    ft_fprintf(2, VV_ENTER_FMT, proginfo()->name, f);
}

void        vv_quit(char *f)
{
    if (!PI_ISOPT(proginfo()->opt, VM_VVERBOSE_OPT))
        return ;
    ft_fprintf(2, VV_QUIT_FMT, proginfo()->name, f);
}

void        vv_msg(char *msg)
{
    if (!PI_ISOPT(proginfo()->opt, VM_VVERBOSE_OPT))
        return ;
    ft_fprintf(2, "%s: {yellow}%s{eoc}\n", proginfo()->name, msg);
}

void        vv_dump(void)
{
    if (!PI_ISOPT(proginfo()->opt, VM_VVERBOSE_OPT))
        return ;
    vm_dump(1);
}
