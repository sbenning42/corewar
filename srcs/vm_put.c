/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 21:27:43 by                   #+#    #+#             */
/*   Updated: 2017/04/12 22:03:33 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	vm_put_byte(t_vm *vm, size_t offset)
{
	unsigned char	o;

	o = vm->memory[offset];
	ft_printf((o ? "{gr}%02x {eoc}" : "%02x "), o);
}

void	vm_put64(t_vm *vm, size_t start, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		vm_put_byte(vm, start + i);
		++i;
	}
	ft_printf("\n");
}

void	vm_put(t_vm *vm, size_t start, size_t size, int rel)
{
	size_t	i;
	size_t	stop;
	size_t	rest;
	void	*addr;

	i = 0;
	stop = size / 64;
	rest = size % 64;
	addr = (rel ? NULL : (vm->memory + start));
	while (i <= stop)
	{
		addr += i * 64;
		if (i == stop && rest)
		{
			ft_printf("%06x : ", addr);
			vm_put64(vm, start + i * 64, rest);
		}
		else if (i < stop)
		{
			ft_printf("%06x : ", addr);
			vm_put64(vm, start + i * 64, 64);
		}
		++i;
	}
}
