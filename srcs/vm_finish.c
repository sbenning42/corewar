/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_finish.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 09:47:42 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/11 12:01:34 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int				vm_finish_dump(void)
{
    if (VM_A_CONFIG.dump > 0)
    {
        if (VM_SINGLE->tic >= (unsigned long)VM_A_CONFIG.dump)
        {
			vm_put_players();
            ft_print_legit_memory(VM_A_MEMORY.buffer, VM_A_CONFIG.mem_size);
            return (1);
        }
    }
	return (0);

}

void			vm_msg_dec_cycle_to_die(void)
{
	ft_printf("* Decrementing cycle to die to %u", VM_A_CONFIG.cycle_to_die);
}

void			vm_msg_dec_cycle_to_die_to_much(void)
{
	vm_msg_dec_cycle_to_die();
	ft_printf("\tCause to much live's in a check cycle\n");
}

void			vm_msg_dec_cycle_to_die_not_enougth(void)
{
	vm_msg_dec_cycle_to_die();
	ft_printf("\tCause not enougth dead since max check cycle\n");
}

int				vm_finish_live(void)
{
	t_list		*l;
	t_process	*p;

	if (VM_A_CONFIG.cycle < VM_A_CONFIG.cycle_to_die)
	{
		(&VM_A_CONFIG)->cycle += 1;
		return (0);
	}
	l = VM_A_PROCESS;
	while (l)
	{
		p = (t_process *)l->content;
		if (p->live <= 0)
		{
			vm_declare_dead(p);
			p->dead = 1;
		}
		else
		{
			p->live = 0;
		}
		l = l->next;
	}
	(&VM_A_CONFIG)->cycle = 0;
	if (VM_A_CONFIG.nbr_live_check >= VM_A_CONFIG.nbr_live)
	{
		(&VM_A_CONFIG)->cycle_to_die -= VM_A_CONFIG.cycle_delta;
		vm_msg_dec_cycle_to_die_to_much();
		(&VM_A_CONFIG)->nbr_live_check = 0;
		(&VM_A_CONFIG)->nbr_checks = 0;
	}
	else
	{
		if (VM_A_CONFIG.nbr_checks > VM_A_CONFIG.max_checks)
		{
			(&VM_A_CONFIG)->cycle_to_die -= VM_A_CONFIG.cycle_delta;
			vm_msg_dec_cycle_to_die_not_enougth();
			(&VM_A_CONFIG)->nbr_checks = 0;
		}
		else
			(&VM_A_CONFIG)->nbr_checks += 1;
	}
	return (0);
}
