#include "ft_automaton.h"

void            nfa_l_del(void *c, size_t s)
{
    free(c);
    (void)s;
}

void            nfa_state_del(void *content, size_t size)
{
    t_state     *state;

    state = *(t_state **)content;
    ft_lstdel(&state->trans, nfa_l_del);
    ft_lstdel(&state->eps_trans, nfa_l_del);
    free(state);
    free(content);
    (void)size;
}

void            nfa_all_state_del(t_list **l)
{
    ft_lstdel(l, nfa_state_del);
}

void            nfa_del(t_nfa **nfa)
{
    if (!*nfa)
        return ;
    ft_memdel((void **)nfa);
}

void            nfa_deep_del(t_nfa **nfa)
{
    if (!*nfa)
        return ;
    nfa_all_state_del(&(*nfa)->state);
    ft_memdel((void **)nfa);
}
