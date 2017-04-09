#include "libft.h"

void        ft_print_memory_set(void *m, size_t i, size_t size)
{
    size_t  j;
    unsigned char   o1;
    unsigned char   o2;

    ft_printf("%p:\t", m + i);
    j = 0;
    while (j < 16 && i + j < size)
    {
        o1 = *(unsigned char *)(m + i + j);
        o2 = (j + 1 < 16 ? *(unsigned char *)(m + i + j + 1) : 0);
        ft_printf("%02x%02x%c", o1, o2, ((j + 2 < 16) ? ' ' : '\t'));
        j += 2;
    }
    j = 0;
    while (j < 16 && i + j < size)
    {
        o1 = *(unsigned char *)(m + i + j);
        if (!ft_isprint(o1))
            o1 = '.';
        o2 = (j + 1 < 16 ? *(unsigned char *)(m + i + j + 1) : 0);
        if (!ft_isprint(o2))
            o2 = '.';
        ft_printf("%c%c%s", o1, o2, ((j + 2 < 16) ? "" : "\n"));
        j += 2;
    }
}


int         is_legit(void *m, size_t size)
{
    size_t  i;

    i = 0;
    while (i < size)
    {
        if (*(unsigned char *)(m + i))
            return (1);
        ++i;
    }
    return (0);
}

void        ft_print_memory(void *m, size_t size)
{
    size_t  i;

    i = 0;
    while (i < size)
    {
        if (is_legit(m + i, 16))
            ft_print_memory_set(m, i, size);
        i += 16;
    }
}
