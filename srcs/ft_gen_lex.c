#include "ft_lexer.h"

static t_lexer      **s_lex(void)
{
    static t_lexer  *lex;

    return (&lex);
}

static char         **s_scan(void)
{
    static char     *scan;

    return (&scan);
}

static int          *s_offset(void)
{
    static int      offset;

    return (&offset);
}

void                ft_set_lex(t_lexer *lexer)
{
    *s_lex() = lexer;
}

void                ft_lex_start_scan(char *scan)
{
    *s_scan() = scan;
    *s_offset() = 0;
}

void                ft_quit_lex(void)
{
    *s_scan() = NULL;
    *s_offset() = 0;
    *s_lex() = NULL;
}

void                ft_kill_lex(void)
{
    *s_scan() = NULL;
    *s_offset() = 0;
    lexer_del(s_lex());
}

t_lexer             *ft_gen_lex(char **regex, char **key, int size)
{
    t_lexer         *lexer;

    lexer = lexer_new(regex, key, size);
    if (!lexer)
        return (NULL);
    if (lexer_computize(lexer))
        return (NULL);
    return (lexer);
}

t_lexem             *lexem_new(int id, char *key, char *scan, int size)
{
    t_lexem         *lexem;

    if (!(lexem = (t_lexem *)ft_memalloc(sizeof(t_lexem))))
        return (NULL);
    lexem->id = id;
    lexem->key = key;
    lexem->size = size;
    lexem->value = ft_strsub(scan, 0, size);
    if (!lexem->value)
    {
        free(lexem);
        return (NULL);
    }
    return (lexem);
}

t_lexem            *ft_lex(void)
{
    t_list          *l;
    t_analyzer      *analyze;
    t_lexem         *lexem;
    int             size;
    int             max;
    t_analyzer      *max_analyze;

    if (!*s_scan() || !*s_lex())
        return (NULL);
    while (**s_scan() == ' ' || **s_scan() == '\t')
    {
        *s_scan() += 1;
        *s_offset() += 1;
    }
    l = (*s_lex())->analyzer;
    max = 0;
    while (l)
    {
        analyze = (t_analyzer *)l->content;
        size = nfa_match(analyze->nfa, *s_scan());
        if (size > max)
        {
            max = size;
            max_analyze = analyze;
        }
        l = l->next;
    }
    if (!max && **s_scan())
        return (lexem_new(-1, "{red}LEXERROR{eoc}", *s_scan(), (int)ft_strlen(*s_scan())));
    else if (!**s_scan())
        return (NULL);
    lexem = lexem_new(max_analyze->id, max_analyze->key, *s_scan(), max);
    if (!lexem)
        return (NULL);
    *s_scan() += max;
    *s_offset() += max;
    return (lexem);
}

t_lexem            *ft_lex_eval(void)
{
    t_lexem         *lexem;

    lexem = NULL;
    return (lexem);
}

void                lexem_dump(t_lexem *lexem)
{
    char            key[2048];
    char            fmt[2048];

    ft_sprintf(fmt, "%s", lexem->key);
    ft_sprintf(key, fmt);
    ft_printf("Lexem: %25s : [%s]\n", key, lexem->value);
}

void                lexem_del(t_lexem **lexem)
{
    if (!*lexem)
        return ;
    if ((*lexem)->value)
        ft_memdel((void **)&(*lexem)->value);
    ft_memdel((void **)lexem);
}
