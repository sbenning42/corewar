#include "vm.h"

void                vm_print_memory64(void *m, void *r, char *c, size_t s)
{
    size_t          i;
    unsigned char   o;

    ft_printf("0x%04x : ", m - r);
    i = 0;
    while (i < s)
    {
        o = *(unsigned char *)(m + i);
        ft_printf((o ? "{gr}%s%02x{eoc} " : "%s%02x{eoc} "), c, o);
        ++i;
    }
    ft_printf("\n");
}

void                vm_print_memory(void *m, size_t s, char *c, int rel)
{
    void            *r;
    char            cfmt[512];
    size_t          i;

    *cfmt = 0;
    if (c)
        ft_sprintf(cfmt, c);
    r = (rel ? m : NULL);
    i = 0;
    while (i < s)
    {
        vm_print_memory64((void *)(m + i), r, cfmt, ((s - i) > 64 ? 64 : s));
        i += 64;
    }
}
