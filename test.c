/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 23:48:11 by                   #+#    #+#             */
/*   Updated: 2017/04/19 11:32:19 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int				ft_endian(void)
{
	int			e;

	e = 1;
	return (*(char *)&e);
}

typedef enum	e_e_swap
{
	Char,
	Short,
	Int
}				t_e_swap;

typedef union	u_u_swap
{
	char		c;
	short		s;
	int			i;
	char		t[4];
}				t_u_swap;

typedef struct	s_swap
{
	t_e_swap	t;
	t_u_swap	v;
}				t_swap;

int				g_size;

int				ft_intswap(int i)
{
	t_swap		o;
	t_swap		s;

	o.v.i = i;
	s.v.t[0] = o.v.t[3];
	s.v.t[1] = o.v.t[2];
	s.v.t[2] = o.v.t[1];
	s.v.t[3] = o.v.t[0];
	return (s.v.i);
}

short			ft_shortswap(short s)
{
	t_swap		o;
	t_swap		sw;

	o.v.s = s;
	sw.v.t[0] = o.v.t[1];
	sw.v.t[1] = o.v.t[0];
	printf("Sshort : %hd, %hd\n", s, sw.v.s);
	return (sw.v.s);
}

int				ft_bigint(int i)
{
	return ((ft_endian() ? ft_intswap(i) : i));
}

int				ft_littleint(int i)
{
	return ((ft_endian() ? i : ft_intswap(i)));
}

short			ft_bigshort(short s)
{
	return ((ft_endian() ? ft_shortswap(s) : s));
}

short			ft_littleshort(short s)
{
	return ((ft_endian() ? s : ft_shortswap(s)));
}

int				bin_pc(int pc, int cycle)
{
	printf("bin_pc : pc : %d, cycle : %d, binpc : %d\n", pc, cycle, ((pc % cycle) + (pc < 0 ? cycle : 0)));
	return (((pc % cycle) + (pc < 0 ? cycle : 0)));
}

unsigned char	bin_access(unsigned char bin[], int pc)
{
	return (bin[bin_pc(pc, g_size)]);
}

char			bin_char(unsigned char bin[], int pc)
{
	return ((char)bin_access(bin, pc));
}

short			bin_short(unsigned char bin[], int pc)
{
	short		s;
	t_swap		sw;

	printf("pc : %d\n", pc);
	sw.v.t[0] = bin_access(bin, pc++);
	printf("pc : %d\n", pc);
	sw.v.t[1] = bin_access(bin, pc);
	printf("[%hhx][%hhx]\n", sw.v.t[0], sw.v.t[1]);
	//((unsigned char *)&s)[0] = bin_access(bin, pc++);
	//((unsigned char *)&s)[1] = bin_access(bin, pc);
	printf("Bshort : %hd, %d\n", sw.v.s, (int)sw.v.s);
	return (sw.v.s);
}

int				bin_int(unsigned char bin[], int pc)
{
	int			i;

	((unsigned char *)&i)[0] = bin_access(bin, pc++);
	((unsigned char *)&i)[1] = bin_access(bin, pc++);
	((unsigned char *)&i)[2] = bin_access(bin, pc++);
	((unsigned char *)&i)[3] = bin_access(bin, pc);
	return (i);
}

int				read_int(unsigned char bin[], int *pc)
{
	int			i;

	i = ft_bigint(bin_int(bin, *pc));
	printf("Rint : %d, pc = %d\n", i, *pc);
	*pc = bin_pc(*pc + 4, g_size);
	return (i);
}

int				read_short(unsigned char bin[], int *pc)
{
	short		s;

	s = ft_bigshort(bin_short(bin, *pc));
	printf("Rshort : %hd, %d, pc = %d\n", s, (int)s, *pc);
	*pc = bin_pc(*pc + 2, g_size);
	return ((int)s);
}

int				read_char(unsigned char bin[], int *pc)
{
	char		c;

	c = bin_char(bin, *pc);
	printf("Rchar : %hhd, %d, pc = %d\n", c, (int)c, *pc);
	*pc = bin_pc(*pc + 1, g_size);
	printf("Rchar : %hhd, %d, pc = %d\n", c, (int)c, *pc);
	return ((int)c);
}

typedef enum	e_e_arg
{
	reg_arg,
	dir_arg,
	ind_arg
}				t_e_arg;

typedef struct	s_arg
{
	t_e_arg		type;
	int			val;
}				t_arg;

typedef struct	s_ins_arg
{
	t_arg		args[4];
	int			nb_arg;
}				t_ins_arg;

int				fill_reg(t_arg *arg, unsigned char bin[], int *pc, int null)
{
	arg->type = reg_arg;
	arg->val = read_char(bin, pc);
	return (1);
	(void)null;
}

int				fill_ind(t_arg *arg, unsigned char bin[], int *pc, int null)
{
	arg->type = ind_arg;
	arg->val = read_short(bin, pc);
	return (2);
	(void)null;
}

int				fill_dir(t_arg *arg, unsigned char bin[], int *pc, int label_size)
{
	arg->type = dir_arg;
	if (label_size == 4)
		arg->val = read_int(bin, pc);
	else
		arg->val = read_short(bin, pc);
	return (label_size);
}

int				fill_null(t_arg *null0, unsigned char null1[], int *null2, int null3)
{
	(void)null0;
	(void)null1;
	(void)null2;
	(void)null3;
	return (0);
}

static int		(*dispatch(unsigned char ocp))(t_arg *, unsigned char [], int *, int)
{
	ocp &= 0xc0;
	if (ocp == 0x40)
		return (fill_reg);
	else if (ocp == 0x80)
		return (fill_dir);
	else if (ocp == 0xc0)
		return (fill_ind);
	return (fill_null);
}

int				fill_args(t_ins_arg *ins, unsigned char ocp, int label_size, unsigned char bin[], int pc)
{
	int			size;

	size = 0;
	ins->nb_arg = 0;
	while (ocp)
	{
		size += dispatch(ocp)(ins->args + ins->nb_arg, bin, &pc, label_size);
		ins->nb_arg += 1;
		ocp <<= 0x2;
	}
	printf("Size arg : %d\n", size);
	printf("nb arg : %d\n", ins->nb_arg);
	return (size);
}

int 			main()
{
	unsigned char	bin[] = {0x1, 0x0, 0x0, 0x0, 0x1, 0x9, 0x64, 0x1, 0xff, 0xfb, 0x3};
	unsigned char	ocp;
	int				pc;
	int				size;

	pc = 0;
	t_ins_arg	ins;

	g_size = 11;
	pc = bin_pc(pc + 1, g_size);
	pc = bin_pc(pc + fill_args(&ins, 0x80, 4, bin, pc), g_size);
	
	printf("Id live : %d, pc %d\n", ins.args[0].val, pc);

	pc = bin_pc(pc + 1, g_size);
	ocp = bin_access(bin, pc);
	
	pc = bin_pc(pc + 1, g_size);
	printf("PC before arg %d\n", pc);
	pc = bin_pc(pc + fill_args(&ins, ocp, 2, bin, pc), g_size);
	
	printf("Arg 0 : %d, pc %d\n", ins.args[0].val, pc);
	printf("Arg 1 : %d, pc %d\n", ins.args[1].val, pc);
	printf("Arg 2 : %d, pc %d\n", ins.args[2].val, pc);

	return (0);
}
