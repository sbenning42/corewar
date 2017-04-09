#include "ft_automaton.h"

int             nfa_is_terminal(t_nfa *nfa, t_list *tokens)
{
    return (tokens\
            && (nfa->terminal == *(t_state **)tokens->content\
                || nfa_is_terminal(nfa, tokens->next)));
}

t_list          *nfa_get_start_tokens(t_nfa *nfa)
{
    t_list      *tokens;


    if (!(tokens = ft_lstnew(&nfa->initial, sizeof(t_state *))))
        return (NULL);
    nfa_clone_tokens(&tokens);
    return (tokens);
}

int             nfa_match(t_nfa *nfa, char *scan)
{
    t_list      *tokens;
    int         max_match;

    if (!(tokens = nfa_get_start_tokens(nfa)))
        return (0);
    max_match = 0;
    max_match = nfa_eval_tokens_step(nfa, &tokens, scan, 0, &max_match);
    ft_lstdel(&tokens, nfa_l_del);
    return (max_match);
}

int             nfa_match_all(t_nfa *nfa, char *scan)
{
    t_list      *tokens;
    int         ret;

    if (!(tokens = nfa_get_start_tokens(nfa)))
        return (0);
    nfa_eval_tokens(&tokens, scan);
    ret = nfa_is_terminal(nfa, tokens);
    ft_lstdel(&tokens, nfa_l_del);
    return (ret);
}

t_nfa           *nfa_regex2nfa(char *regex)
{
    t_list      *explicit;
    t_list      *rpn;
    t_nfa       *nfa;

    if (!*regex)
        return (nfa_epsilon());
    if (!(explicit = regex2explicit(regex)))
        return (NULL);
    rpn = explicit2rpn(explicit);
    ft_lstdel(&explicit, nfa_l_del);
    if (!rpn)
        return (NULL);
    nfa = rpn2nfa(rpn);
    ft_lstdel(&rpn, nfa_l_del);
    if (!nfa)
        ft_fprintf(2, "{red}Syntax error. . .{eoc}\n");
    return (nfa);
}
