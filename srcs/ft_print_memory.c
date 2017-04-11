#include "libft.h"

char		*g_color[] = {\
	"{blue}",\
	"{red}",\
	"{green}",\
	"{yellow}",\
	NULL\
};

void        ft_print_memory_set(void *m, size_t i, size_t size)
{
    size_t  j;
    unsigned char   o;

    ft_printf("0x%04x : ", i);
    j = 0;
    while (j < 64 && i + j < size)
    {
        o = *(unsigned char *)(m + i + j);
        ft_printf((o ? "{gr}%02x{eoc} " : "%02x "), o);
        ++j;
    }
	ft_printf("\n");
}

void        ft_print_memory_legit_set(void *m, size_t i, size_t size, char *fmt)
{
    size_t  j;
    unsigned char   o;

    ft_printf("0x%04x : ", i);
    j = 0;
    while (j < 64 && i + j < size)
    {
        o = *(unsigned char *)(m + i + j);
        ft_printf((o ? "%s{gr}%02x {eoc}" : "%s%02x {eoc}"), fmt, o);
        ++j;
    }
	ft_printf("\n");
}

int         is_legit(void *m, size_t size)
{
    size_t  i;

    i = 0;
    while (i < size)
    {
        if (*(unsigned char *)(m + i))
            return (1);
        ++i;
    }
    return (0);
}

void        ft_print_memory(void *m, size_t size)
{
    size_t  i;

    i = 0;
    while (i < size)
    {
        ft_print_memory_set(m, i, size);
        i += 64;
    }
}

void		pcolor(char **c)
{
	char	fmt[1024];

	while (*c)
	{
		ft_sprintf(fmt, *c);
		ft_printf("%s        {eoc}", fmt);
		++c;
	}
	ft_printf("\n\n");
}

void        ft_print_legit_memory(void *m, size_t size)
{
    size_t  i;
	char	**color;
	char	fmt[1024];
	int		flag;

	color = g_color;
	ft_sprintf(fmt, *color);
    i = 0;
	flag = 0;
    while (i < size)
    {
		if (is_legit(m + i, 64))
		{
        	ft_print_memory_legit_set(m, i, size, fmt);
			flag = 1;
		}
		else if (flag)
		{
			flag = 0;
			++color;
			if (*color)
			{
				ft_sprintf(fmt, *color);
       // 		ft_print_memory_legit_set(m, i, size, "");
			}
		}
	//	else
      //  	ft_print_memory_legit_set(m, i, size, "");
        i += 64;
    }
}
