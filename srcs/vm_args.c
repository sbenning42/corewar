/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 11:31:10 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/12 12:13:26 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			set_args(char **k, char **re, size_t size)
{
	t_lexer		*lexer;

	if (!(lexer = ft_gen_lex(re, k, size)))
		vm_fatal(VM_EMALLOC);
	ft_set_lex(lexer);
	ft_lex_start_scan(main_av()[1]);
}

t_lexem			*get_arg(void)
{
	static int	i = 1;
	t_lexem		*l;

	if (!(l = ft_lex()) && ++i < main_ac())
	{
		ft_lex_start_scan(main_av()[i]);
		l = ft_lex();
	}
	return (l);
}

void			del_args(void)
{
	ft_kill_lex();
}
