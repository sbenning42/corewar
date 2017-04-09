#include "ft_file.h"

t_file      *open_file(char *name, int mode)
{
    t_file  *f;

    f = (t_file *)ft_memalloc(sizeof(t_file));
    if (!f)
        return (NULL);
    f->name = ft_strdup(name);
    if (!f->name)
    {
        free(f);
        return (NULL);
    }
    f->mode = mode;
    f->fd = open(name, mode, 0755);
    if (f->fd < 0)
    {
        free(f->name);
        free(f);
        return (NULL);
    }
    return (f);
}

void        close_file(t_file **f)
{
    if ((*f)->fd >= 0)
        close((*f)->fd);
    free((*f)->name);
    if ((*f)->line)
        free((*f)->line);
    if ((*f)->binary)
        free((*f)->binary);
    free(*f);
    *f = NULL;
}

int         read_file(t_file *f)
{
    int     status;

    if (f->line)
        ft_memdel((void **)&f->line);
    status = get_next_line(f->fd, &f->line);
    if (status > 0)
        f->li += 1;
    return (status);
}

int                 read_binary_file(t_file *f)
{
    size_t          size;
    size_t          asize;
    size_t          offset;
    int             ret;
    unsigned char   binary[2048];
    unsigned char   *tmp;

    asize = 0;
    size = 0;
    offset = 2048 * 2;
    if (f->binary)
        ft_memdel((void **)&f->binary);
    while ((ret = read(f->fd, binary, 2048)) > 0)
    {
        if (size + ret > asize)
        {
            tmp = f->binary;
            if (!(f->binary = ft_memalloc(sizeof(unsigned char) * (asize + offset))))
                return (-1);
            asize += offset;
            if (size)
                ft_memcpy(f->binary, tmp, size * sizeof(unsigned char));
            if (tmp)
                free(tmp);
        }
        ft_memcpy(f->binary + size, binary, ret);
        size += ret;
    }
    f->binary_size = size;
    return (0);
}

int         ft_realloc(void **m, int dsize, int size)
{
    void    *tmp;

    tmp = *m;
    if (!(*m = ft_memalloc(size)))
    {
        *m = tmp;
        return (-1);
    }
    if (tmp && dsize)
        ft_memcpy(*m, tmp, dsize);
    if (tmp)
        ft_memdel(&tmp);
    return (0);
}
