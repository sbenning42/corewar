/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:25:50 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/12 11:30:26 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_main		*s_main(void)
{
	static t_main	m;

	return (&m);
}

void				set_main(int ac, char **av)
{
	s_main()->ac = ac;
	s_main()->av = av;
}

int					main_ac(void)
{
	return (s_main()->ac);
}

char				**main_av(void)
{
	return (s_main()->av);
}

char				*prog_name(void)
{
	return (s_main()->av[0]);
}
