#include "ft_automaton.h"

static t_nfa    *nfa_kleen(t_nfa *origin)
{
    t_nfa       *nfa;
    
    if (!(nfa = nfa_new_atom()))
        return (NULL);
    nfa_merge(nfa, origin);
    if (nfa_eps_trans(nfa->initial, origin->initial))
        return (NULL);
    if (nfa_eps_trans(origin->terminal, nfa->terminal))
        return (NULL);
    return (nfa);
}

t_nfa           *nfa_kleen_point(t_nfa *origin)
{
    t_nfa       *nfa;

    if (!(nfa = nfa_kleen(origin)))
        return (NULL);
    if (nfa_eps_trans(nfa->initial, nfa->terminal))
        return (NULL);
    nfa_del(&origin);
    return (nfa);
}

t_nfa           *nfa_kleen_plus(t_nfa *origin)
{
    t_nfa       *nfa;

    if (!(nfa = nfa_kleen(origin)))
        return (NULL);
    if (nfa_eps_trans(origin->terminal, origin->initial))
        return (NULL);
    nfa_del(&origin);
    return (nfa);
}

t_nfa           *nfa_kleen_star(t_nfa *origin)
{
    t_nfa       *nfa;

    if (!(nfa = nfa_kleen(origin)))
        return (NULL);
    if (nfa_eps_trans(nfa->initial, nfa->terminal))
        return (NULL);
    if (nfa_eps_trans(origin->terminal, origin->initial))
        return (NULL);
    nfa_del(&origin);
    return (nfa);
}
