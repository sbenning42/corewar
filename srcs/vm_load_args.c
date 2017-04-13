/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_load_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 14:54:26 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/13 20:27:57 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			vm_handler_arg_error(t_vm *vm, char *arg)
{
	vm_fatal(VM_EUSAGE);
	(void)vm;
	(void)arg;
}

static t_vm_args_h	g_args_handler[] = {\
	{VM_ERR_ARG, vm_handler_arg_error},\
	{VM_AFF_ARG, vm_handler_arg_affiche},\
	{VM_DUMP_ARG, vm_handler_arg_dump},\
	{VM_STEP_ARG, vm_handler_arg_step},\
	{VM_PNUM_ARG, vm_handler_arg_pnum},\
	{VM_VERB_ARG, vm_handler_arg_verbose},\
	{VM_NUMBER_ARG, vm_handler_arg_champion},\
	{VM_CHAMP_ARG, vm_handler_arg_champion}\
};

static void			(*dispatch(int id))(t_vm *, char *)
{
	size_t			i;

	i = 0;
	while (i < TABSIZE(g_args_handler))
	{
		if (g_args_handler[i].id == id)
			return (g_args_handler[i].func);
		++i;
	}
	return (vm_handler_arg_error);
}

void				vm_load_args(t_vm *vm)
{
	t_lexem			*l;

	while ((l = get_arg()))
	{
		dispatch(l->id)(vm, l->value);
		lexem_del(&l);
	}
	del_args();
}
