#ifndef FT_FILE_H
# define FT_FILE_H

# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>

typedef struct s_file   t_file;

struct                  s_file
{
    char                *name;
    int                 mode;
    int                 fd;
    char                *line;
    int                 li;
};

t_file                  *open_file(char *name, int mode);
void                    close_file(t_file **f);
int                     read_file(t_file *f);
size_t					read_binary_file(t_file *f, unsigned char *buff, size_t size);
int                     ft_realloc(void **m, int dsize, int size);

#endif
