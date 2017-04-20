/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 10:24:20 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/19 13:15:58 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define COREWAR_EXEC_MAGIC	0xea83f3

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"
# define LABEL_CHAR			':'
# define SEPARATOR_CHAR		','
# define DIRECT_CHAR		'%'
# define COMMENT_CHAR		'#'
# define COMMAND_CHAR		'.'
# define LITERAL_CHAR		'"'

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define T_REG				0x1
# define T_DIR				0x2
# define T_IND				0x3
# define T_LAB				0x8
# define T_NOP				0x10

# define MAX_ARGS_NUMBER	4
# define PROG_NAME_LENGTH	128
# define COMMENT_LENGTH		2048

# define MAX_PLAYERS        4
# define MEM_SIZE           (4 * 1024)
# define IDX_MOD            (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE     (MEM_SIZE / 6)
# define REG_SIZE           4
# define REG_NUMBER         16
# define CYCLE_TO_DIE       1536
# define CYCLE_DELTA        50
# define NBR_LIVE           21
# define MAX_CHECKS         10

# define OP_LIVE_I			0
# define ASM_LIVE_ID		"live"
# define ASM_LIVE_DESC		"alive"
# define ASM_LIVE_ARGS		T_DIR, T_NOP, T_NOP, T_NOP

# define OP_LD_I			1
# define ASM_LD_ID			"ld"
# define ASM_LD_DESC		"load"
# define ASM_LD_ARGS		T_DIR | T_IND, T_REG, T_NOP, T_NOP

# define OP_ST_I			2
# define ASM_ST_ID			"st"
# define ASM_ST_DESC		"store"
# define ASM_ST_ARGS		T_REG, T_REG | T_IND, T_NOP, T_NOP

# define OP_ADD_I			3
# define ASM_ADD_ID			"add"
# define ASM_ADD_DESC		"addition"
# define ASM_ADD_ARGS		T_REG, T_REG, T_REG, T_NOP

# define OP_SUB_I			4
# define ASM_SUB_ID			"sub"
# define ASM_SUB_DESC		"soustraction"
# define ASM_SUB_ARGS		T_REG, T_REG, T_REG, T_NOP

# define OP_AND_I			5
# define ASM_AND_ID			"and"
# define ASM_AND_DESC		"et (and  r1, r2, r3   r1&r2 -> r3"
# define ASM_AND_ARGS		T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG, T_NOP

# define OP_OR_I			6
# define ASM_OR_ID			"or"
# define ASM_OR_DESC		"ou  (or   r1, r2, r3   r1 | r2 -> r3"
# define ASM_OR_ARGS		T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG, T_NOP

# define OP_XOR_I			7
# define ASM_XOR_ID			"xor"
# define ASM_XOR_DESC		"ou (xor  r1, r2, r3   r1^r2 -> r3"
# define ASM_XOR_ARGS		T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG, T_NOP

# define OP_ZJMP_I			8
# define ASM_ZJMP_ID		"zjmp"
# define ASM_ZJMP_DESC		"jump if zero"
# define ASM_ZJMP_ARGS		T_DIR, T_NOP, T_NOP, T_NOP

# define OP_LDI_I			9
# define ASM_LDI_ID			"ldi"
# define ASM_LDI_DESC		"load index"
# define ASM_LDI_ARGS		T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG, T_NOP

# define OP_STI_I			10
# define ASM_STI_ID			"sti"
# define ASM_STI_DESC		"store index"
# define ASM_STI_ARGS		T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR, T_NOP

# define OP_FORK_I			11
# define ASM_FORK_ID		"fork"
# define ASM_FORK_DESC		"fork"
# define ASM_FORK_ARGS		T_DIR, T_NOP, T_NOP, T_NOP

# define OP_LLD_I			12
# define ASM_LLD_ID			"lld"
# define ASM_LLD_DESC		"long load"
# define ASM_LLD_ARGS		T_DIR | T_IND, T_REG, T_NOP, T_NOP

# define OP_LLDI_I			13
# define ASM_LLDI_ID		"lldi"
# define ASM_LLDI_DESC		"lomg load index"
# define ASM_LLDI_ARGS		T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG, T_NOP

# define OP_LFORK_I			14
# define ASM_LFORK_ID		"lfork"
# define ASM_LFORK_DESC		"long fork"
# define ASM_LFORK_ARGS		T_DIR, T_NOP, T_NOP, T_NOP

# define OP_AFF_I			15
# define ASM_AFF_ID			"aff"
# define ASM_AFF_DESC		"aff"
# define ASM_AFF_ARGS		T_REG, T_NOP, T_NOP, T_NOP

typedef char				t_arg_type;
typedef struct s_op			t_op;
typedef struct header_s		header_t;

struct						s_op
{
	char					*id;
	unsigned int			opcode;
	unsigned int			nb_arg;
	int						args_type[MAX_ARGS_NUMBER];
	char					*desc;
	unsigned int			cycle;
	unsigned int			carry;
	unsigned int			ocp;
	unsigned int			label_size;
};

struct						header_s
{
	unsigned int			magic;
	char					prog_name[PROG_NAME_LENGTH + 1];
	unsigned int			prog_size;
	char					comment[COMMENT_LENGTH + 1];
};

extern t_op					g_op[];

#endif
