/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 10:45:42 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/12 16:24:03 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void				vm_loop(t_vm *vm)
{
	while (42)
	{
		break ;
	}
	(void)vm;
}

void				vm_cleanup(t_vm *vm)
{
	(void)vm;
}

int					main(int ac, char **av)
{
	t_vm			vm;

	set_main(ac, av);
    vm_setup(&vm);
    vm_loop(&vm);
    vm_cleanup(&vm);
	return (0);
}
