#include "ft_automaton.h"

int             nfa_search_state(t_list *tokens, t_state *state)
{
    return ((tokens\
                && ((state == *(t_state **)tokens->content)\
                    || nfa_search_state(tokens->next, state))));
}

void            nfa_union_tokens(t_list **l1, t_list *l2)
{
    if (!l2)
        return ;
    if (!nfa_search_state(*l1, *(t_state **)l2->content))
        ft_lstadd_back(l1, ft_lstnew(l2->content, sizeof(t_state *)));
    nfa_union_tokens(l1, l2->next);
}

void            nfa_rec_clone_tokens(t_list **tokens, t_list *token)
{
    if (!token)
        return ;
    nfa_union_tokens(tokens, (*(t_state **)token->content)->eps_trans);
    nfa_rec_clone_tokens(tokens, token->next);
}

void            nfa_clone_tokens(t_list **tokens)
{
    nfa_rec_clone_tokens(tokens, *tokens);
}

void            nfa_rec_play_token(t_list **trans, t_list *closure, char c)
{
    t_trans     *cast;

    if (!closure)
        return ;
    cast = (t_trans *)closure->content;
    if (c >= cast->start && c <= cast->end)
        ft_lstadd_back(trans, ft_lstnew(&cast->state, sizeof(t_state *)));
    nfa_rec_play_token(trans, closure->next, c);
}

t_list          *nfa_play_token(t_list *token, char c)
{
    t_list      *trans;

    trans = NULL;
    nfa_rec_play_token(&trans, (*(t_state **)token->content)->trans, c);
    return (trans);
}

void            nfa_rec_play_tokens(t_list **trans, t_list *tokens, char c)
{
    t_list      *l;

    if (!tokens)
        return ;
    if ((l = nfa_play_token(tokens, c)))
        nfa_union_tokens(trans, l);
    ft_lstdel(&l, nfa_l_del);
    nfa_rec_play_tokens(trans, tokens->next, c);
}

void            nfa_play_tokens(t_list **tokens, char c)
{
    t_list      *trans;

    trans = NULL;
    nfa_rec_play_tokens(&trans, *tokens, c);
    ft_lstdel(tokens, nfa_l_del);
    *tokens = trans;
}

void            nfa_eval_tokens(t_list **tokens, char *scan)
{
    if (!*scan || !*tokens)
        return ;
    nfa_play_tokens(tokens, *scan);
    nfa_clone_tokens(tokens);
    nfa_eval_tokens(tokens, scan + 1);
}

int             nfa_eval_tokens_step(t_nfa *nfa, t_list **tokens, char *scan, int size, int *max)
{
    if (!*scan)
        return (*max);
    nfa_play_tokens(tokens, *scan);
    nfa_clone_tokens(tokens);
    if (!*tokens)
        return (*max);
    if (nfa_is_terminal(nfa, *tokens))
        *max = size + 1;
    return (nfa_eval_tokens_step(nfa, tokens, scan + 1, size + 1, max));
}
