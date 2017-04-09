#include "ft_lexer.h"

static int      extend_tab(char ***tab, int size, char *s)
{
    char        **tmp;

    tmp = *tab;
    if (!(*tab = ft_memalloc(sizeof(char *) * (size + 1))))
        return (-1);
    if (size)
    {
        ft_memcpy(*tab, tmp, sizeof(char *) * size);
        ft_memdel((void **)&tmp);
    }
    (*tab)[size] = s;
    return (0);
}

t_lexer         *lexer_new(char **regex, char **key, int size)
{
    t_lexer     *lexer;

    lexer = (t_lexer *)ft_memalloc(sizeof(t_lexer));
    if (!lexer)
        return (NULL);
    lexer->size = size;
    if (size && !(lexer->regex = ft_memalloc(sizeof(char *) * size)))
        return (NULL);
    if (size && !(lexer->key = ft_memalloc(sizeof(char *) * size)))
        return (NULL);
    if (size)
    {
        ft_memcpy(lexer->regex, regex, sizeof(char *) * size);
        ft_memcpy(lexer->key, key, sizeof(char *) * size);
    }
    return (lexer);
}

int             lexer_add(t_lexer *lexer, char *regex, char *key)
{
    if (extend_tab(&lexer->regex, lexer->size, regex))
        return (-1);
    if (extend_tab(&lexer->key, lexer->size, key))
        return (-1);
    lexer->size += 1;
    return (0);
}

int             rec_lexer_computize(t_lexer *lexer, int i)
{
    t_analyzer  analyzer;
    t_list      *l;

    if (i >= lexer->size)
        return (0);
    analyzer.id = i;
    analyzer.regex = lexer->regex[i];
    analyzer.key = lexer->key[i];
    if (!(analyzer.nfa = nfa_regex2nfa(analyzer.regex)))
        return (-1);
    if (!(l = ft_lstnew(&analyzer, sizeof(t_analyzer))))
    {
        nfa_deep_del(&analyzer.nfa);
        return (-1);
    }
    ft_lstadd_back(&lexer->analyzer, l);
    return (rec_lexer_computize(lexer, i + 1));
}

int             lexer_computize(t_lexer *lexer)
{
    return (rec_lexer_computize(lexer, 0));
}
