/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <sbenning@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 18:24:40 by sbenning          #+#    #+#             */
/*   Updated: 2017/03/24 12:58:46 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getopt_arg(char *av, char *charset)
{
	char	*tmp;
	int		to;
	int		o;

	to = 0;
	while (*av)
	{
		tmp = charset;
		o = 1;
		while (*tmp)
		{
			if (*tmp == *av)
			{
				to += o;
				break ;
			}
			o <<= 1;
			++tmp;
		}
		++av;
	}
	return (to);
}

int			ft_getopt(int ac, char **av, char *charset)
{
	int		opt;
	int		j;

	opt = 0;
	j = 0;
	if (!charset || !av)
		return (0);
	while (++j < ac)
	{
		if (av[j][0] != '-')
			break ;
		opt += ft_getopt_arg(av[j] + 1, charset);
	}
	return (opt);
}
