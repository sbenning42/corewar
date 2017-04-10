#ifndef FT_GETOPT_H
# define FT_GETOPT_H

# include "ft_lexer.h"
# include "proginfo.h"

t_lexem *ft_get_arg(void);
int     ft_smart_getopt(char **key, char **regex, int size);
void    ft_del_opt(void);

#endif
