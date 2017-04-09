#include "ft_automaton.h"

int             nfa_add_trans_entry(t_list **trans, t_list *entry)
{
    ft_lstadd_back(trans, entry);
    return (0);
}

int             nfa_add_eps_trans_entry(t_list **eps_trans, t_list *entry)
{
    ft_lstadd_back(eps_trans, entry);
    return (0);
}

int             nfa_add_trans(t_state *state, t_list *trans)
{
    ft_lstadd_back(&state->trans, trans);
    return (0);
}

int             nfa_add_eps_trans(t_state *state, t_list *eps_trans)
{
    ft_lstadd_back(&state->eps_trans, eps_trans);
    return (0);
}

int             nfa_add_state(t_nfa *nfa, t_state *state)
{
    t_list      *l;

    if (!(l = ft_lstnew(&state, sizeof(t_state *))))
        return (-1);
    ft_lstadd_back(&nfa->state, l);
    nfa->nb_state += 1;
    return (0);
}
