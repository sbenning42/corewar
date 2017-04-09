/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 10:45:42 by sbenning          #+#    #+#             */
/*   Updated: 2017/03/31 15:52:23 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

char                *g_key[] = {\
    "{green}Dump{eoc}",\
    "{blue}Player Number{eoc}",\
    "{yellow}Other Opt{eoc}",\
    "{cyan}Param{eoc}"\
};

char                *g_regex[] = {\
    "\\-+[dump|d]",\
    "\\-+[number|n]",\
    "\\-[v|V|s]+",\
    ".*"\
};

static void			set_program_info(int *ac, char ***av)
{
	proginfo_init(*ac, *av, NULL, VM_OPT_CHARSET);
	if (PI_ISOPT(proginfo()->opt, VM_VVERBOSE_OPT))
		PI_SETOPT(proginfo()->opt, VM_VERBOSE_OPT);
	*ac = proginfo()->oarg_c;
	*av = proginfo()->oarg_v;
    vv_enter("ft_smart_getopt");
    ft_smart_getopt(g_key, g_regex, sizeof(g_key) / sizeof(char *));
    vv_quit("ft_smart_getopt");
}

int					main(int ac, char **av)
{
	set_program_info(&ac, &av);
    vm_setup();
    vm_loop();
    vm_cleanup();
	return (0);
}
