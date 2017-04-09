#include "ft_automaton.h"

void            nfa_toogle_final_state(t_state *state)
{
    if (NFA_IS_FINAL(state->final))
        NFA_UNSET_FINAL(state->final);
    else
        NFA_SET_FINAL(state->final);
}

void            nfa_set_initial(t_nfa *nfa, t_state *state)
{
    nfa->initial = state;
}

void            nfa_set_terminal(t_nfa *nfa, t_state *state)
{
    nfa->terminal = state;
}
