#include "ft_lst.h"

void        ft_lstdel_if(t_list **alst, void *ref,\
            int (*fi)(void *, void *, size_t),\
            void (*del)(void *, size_t))
{
    t_list  *p;
    t_list  *n;
    t_list  *tmp;

    tmp = *alst;
    p = NULL;
    while (tmp)
    {
        n = tmp->next;
        if (fi(ref, tmp->content, tmp->content_size))
        {
            ft_lstdelone(&tmp, del);
            if (p)
                p->next = n;
            else
                *alst = n;
        }
        else
            p = tmp;
        tmp = n;
    }

}
