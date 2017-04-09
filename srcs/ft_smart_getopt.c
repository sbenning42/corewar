#include "ft_getopt.h"

t_lexem                 *ft_get_arg(void)
{
    static int          i = 1;
    t_lexem             *l;

    if (!(l = ft_lex()) && ++i < proginfo()->arg_c)
    {
        ft_lex_start_scan(proginfo()->arg_v[i]);
        l = ft_lex();
    }
    return (l);
}

int                     ft_smart_getopt(char **key, char **regex, int size)
{
    t_lexer             *lexer;

    if (!(lexer = ft_gen_lex(regex, key, size)))
        return (-1);
    ft_set_lex(lexer);
    ft_lex_start_scan(proginfo()->arg_v[1]);
    return (0);
}

void                    ft_del_opt(void)
{
    ft_kill_lex();
}
