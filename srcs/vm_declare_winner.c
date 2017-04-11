/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_declare_winner.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 09:41:37 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/11 11:09:43 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		vm_declare_winner(void)
{
	ft_printf(VM_MWIN, VM_A_CONFIG.id_last_live, VM_A_CONFIG.name_last_live);
}

void		vm_declare_live(void)
{
	ft_printf(VM_MLIVE, VM_A_CONFIG.id_last_live, VM_A_CONFIG.name_last_live);
}

void		vm_declare_dead(t_process *p)
{
	ft_printf(VM_MDEAD, p->player->id, p->player->header.prog_name);
}
