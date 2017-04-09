#include "ft_automaton.h"

t_nfa           *nfa_epsilon(void)
{
    t_nfa       *nfa;

    if (!(nfa = nfa_new_atom()))
        return (NULL);
    if (nfa_eps_trans(nfa->initial, nfa->terminal))
        return (NULL);
    return (nfa);
}

t_nfa           *nfa_range(char start, char end)
{
    t_nfa       *nfa;

    if (!(nfa = nfa_new_atom()))
        return (NULL);
    if (nfa_trans(nfa->initial, nfa->terminal, start, end))
        return (NULL);
    return (nfa);
}

t_nfa           *nfa_joker(void)
{
    return (nfa_range(32, 127));
}

t_nfa           *nfa_atom(char c)
{
    return (nfa_range(c, c));
}
