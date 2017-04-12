/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:53:50 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/12 16:15:22 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_vmerror	g_vmerror[] = {\
	{VM_EUSAGE, VM_MUSAGE},\
	{VM_EMALLOC, "Can't perform malloc."},\
	{0, NULL}\
};

char				*vm_strerror(int error)
{
	t_vmerror		*e;

	e = g_vmerror;
	while (e->error)
	{
		if (e->error == error)
			return (e->message);
		++e;
	}
	return ("Unknow error");
}

int					vm_error(int error)
{
	ft_fprintf(2, "%s: %s\n", prog_name(), vm_strerror(error));
	return (error);
}

void				vm_fatal(int error)
{
	vm_error(error);
	exit(1);
}
