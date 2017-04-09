#include "ft_lexer.h"

void            lexer_del_i(void *c, size_t s)
{
    t_analyzer  *a;

    a = (t_analyzer *)c;
    nfa_deep_del(&a->nfa);
    free(c);
    (void)s;
}

void        lexer_del(t_lexer **lexer)
{
    if (!*lexer)
        return ;
    ft_lstdel(&(*lexer)->analyzer, lexer_del_i);
    ft_memdel((void **)&(*lexer)->regex);
    ft_memdel((void **)&(*lexer)->key);
}
/*
t_atoken    *new_atoken(t_tokenizer *tok, char *v)
{
    t_atoken*t;

    if (!(t = ft_memalloc(sizeof(t_atoken))))
        return (NULL);
    t->value = ft_strdup(v);
    t->id = tok->token_id;
    return (t);
}*/
