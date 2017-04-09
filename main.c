#include "libft.h"

int fi(void *ref, void *c, size_t s)
{
    if (*(char *)ref == *(char *)c)
        return (1);
    return (0);
    (void)s;
}

void    del(void *c, size_t s)
{
    free(c);
    (void)s;
}

void    plst(t_list *l)
{
    ft_printf("[%c]", *(char *)l->content);
}

int main()
{
    t_list  *h;
    t_list  *l;

    h = NULL;

    l = ft_lstnew("a", 1);
    ft_lstadd_back(&h, l);

    l = ft_lstnew("b", 1);
    ft_lstadd_back(&h, l);

    l = ft_lstnew("c", 1);
    ft_lstadd_back(&h, l);

    l = ft_lstnew("a", 1);
    ft_lstadd_back(&h, l);

    l = ft_lstnew("b", 1);
    ft_lstadd_back(&h, l);

    ft_lstiter(h, plst);
    ft_printf("\n");
    ft_lstdel_if(&h, "b", fi, del);
    ft_lstiter(h, plst);
    ft_printf("\n");
    ft_lstdel_if(&h, "a", fi, del);
    ft_lstiter(h, plst);
    ft_printf("\n");
    ft_lstdel(&h, del);
    ft_lstiter(h, plst);
    ft_printf("\n");

    return (0);
}
