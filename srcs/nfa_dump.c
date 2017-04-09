#include "ft_automaton.h"

char            *g_fmt[] = {\
    NFA_DUMP_TE_FN,\
    NFA_DUMP_TE_FC,\
    NFA_DUMP_ETE_FN,\
    NFA_DUMP_ETE_FC,\
    NFA_DUMP_SS_FN,\
    NFA_DUMP_SS_FC,\
    NFA_DUMP_ST_FN,\
    NFA_DUMP_ST_FC,\
    NFA_DUMP_SET_FN,\
    NFA_DUMP_SET_FC,\
    NFA_DUMP_ND_FN,\
    NFA_DUMP_ND_FC,\
    NFA_DUMP_NDA_FN,\
    NFA_DUMP_NDA_FC,\
    NULL\
};

void            nfa_dump_trans_entry(t_list *l, int color)
{
    t_trans     *t;

    t = (t_trans *)l->content;
    ft_printf(g_fmt[color + NFA_DUMP_TE_I],\
            (t->start > 32 ? t->start : '\0'), (t->end < 127 ? t->end : '\0'), (long)t->state & (long)NFA_DM);
}

void            nfa_dump_trans(t_list *l, int color)
{
    if (l)
    {
        nfa_dump_trans_entry(l, color);
        nfa_dump_trans(l->next, color);
    }
}

void            nfa_dump_eps_trans_entry(t_list *l, int color)
{
    ft_printf(g_fmt[color + NFA_DUMP_ETE_I],\
            (long)*(t_state **)l->content & (long)NFA_DM);
}

void            nfa_dump_eps_trans(t_list *l, int color)
{
    if (l)
    {
        nfa_dump_eps_trans_entry(l, color);
        nfa_dump_eps_trans(l->next, color);
    }
}

void            nfa_dump_state(t_state *state, int color)
{
    ft_printf(g_fmt[color + NFA_DUMP_SS_I],\
            (NFA_IS_FINAL(state->final) ? "FINAL" : "NON FINAL"), (long)state & (long)NFA_DM);
    ft_printf(g_fmt[color + NFA_DUMP_ST_I]);
    nfa_dump_trans(state->trans, color);
    ft_printf(g_fmt[color + NFA_DUMP_SET_I]);
    nfa_dump_eps_trans(state->eps_trans, color);
}

void            nfa_dump_all_state(t_list *state, int color)
{
    if (state)
    {
        nfa_dump_state(*(t_state **)state->content, color);
        nfa_dump_all_state(state->next, color);
    }
}

void            nfa_dump(t_nfa *nfa, int color)
{
    if (!nfa)
    {
        ft_printf(g_fmt[color + NFA_DUMP_ND_I]);
        return ;
    }
    ft_printf(g_fmt[color + NFA_DUMP_NDA_I],\
            nfa->nb_state, (long)nfa->initial & (long)NFA_DM, (long)nfa->terminal & (long)NFA_DM);
    nfa_dump_all_state(nfa->state, color);
}
