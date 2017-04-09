#include "ft_automaton.h"

t_nfa           *nfa_conjonction(t_nfa *left, t_nfa *right)
{
    t_nfa       *nfa;

     if (!(nfa = nfa_new_atom()))
        return (NULL);
    nfa_merge(nfa, left);
    nfa_merge(nfa, right);
    if (nfa_eps_trans(nfa->initial, left->initial))
        return (NULL);
    if (nfa_eps_trans(left->terminal, right->initial))
        return (NULL);
    if (nfa_eps_trans(right->terminal, nfa->terminal))
        return (NULL);
    nfa_del(&left);
    nfa_del(&right);
    return (nfa);
}

t_nfa           *nfa_disjonction(t_nfa *left, t_nfa *right)
{
    t_nfa       *nfa;

    if (!(nfa = nfa_new_atom()))
        return (NULL);
    nfa_merge(nfa, left);
    nfa_merge(nfa, right);
    if (nfa_eps_trans(nfa->initial, left->initial))
        return (NULL);
    if (nfa_eps_trans(nfa->initial, right->initial))
        return (NULL);
    if (nfa_eps_trans(left->terminal, nfa->terminal))
        return (NULL);
    if (nfa_eps_trans(right->terminal, nfa->terminal))
        return (NULL);
    nfa_del(&left);
    nfa_del(&right);
    return (nfa);
}
