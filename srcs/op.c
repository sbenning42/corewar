/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 10:46:52 by sbenning          #+#    #+#             */
/*   Updated: 2017/03/30 18:42:01 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** {id, opcode, nb_args, args_type, description, cycle, carry, ocp, label_size}
*/

t_op	g_op[] = {\
	{ASM_LIVE_ID, 1, 1, {ASM_LIVE_ARGS}, ASM_LIVE_DESC, 10, 0, 0, 4},\
	{ASM_LD_ID, 2, 2, {ASM_LD_ARGS}, ASM_LD_DESC, 5, 1, 1, 4},\
	{ASM_ST_ID, 3, 2, {ASM_ST_ARGS}, ASM_ST_DESC, 5, 0, 1, 0},\
	{ASM_ADD_ID, 4, 3, {ASM_ADD_ARGS}, ASM_ADD_DESC, 10, 1, 1, 0},\
	{ASM_SUB_ID, 5, 3, {ASM_SUB_ARGS}, ASM_SUB_DESC, 10, 1, 1, 0},\
	{ASM_AND_ID, 6, 3, {ASM_AND_ARGS}, ASM_AND_DESC, 6, 1, 1, 4},\
	{ASM_OR_ID, 7, 3, {ASM_OR_ARGS}, ASM_OR_DESC, 6, 1, 1, 4},\
	{ASM_XOR_ID, 8, 3, {ASM_XOR_ARGS}, ASM_XOR_DESC, 6, 1, 1, 4},\
	{ASM_ZJMP_ID, 9, 1, {ASM_ZJMP_ARGS}, ASM_ZJMP_DESC, 20, 0, 0, 2},\
	{ASM_LDI_ID, 10, 3, {ASM_LDI_ARGS}, ASM_LDI_DESC, 25, 0, 1, 2},\
	{ASM_STI_ID, 11, 3, {ASM_STI_ARGS}, ASM_STI_DESC, 25, 0, 1, 2},\
	{ASM_FORK_ID, 12, 1, {ASM_FORK_ARGS}, ASM_FORK_DESC, 800, 0, 0, 2},\
	{ASM_LLD_ID, 13, 2, {ASM_LLD_ARGS}, ASM_LLD_DESC, 10, 1, 1, 4},\
	{ASM_LLDI_ID, 14, 3, {ASM_LLDI_ARGS}, ASM_LLDI_DESC, 50, 1, 1, 2},\
	{ASM_LFORK_ID, 15, 1, {ASM_LFORK_ARGS}, ASM_LFORK_DESC, 1000, 0, 0, 2},\
	{ASM_AFF_ID, 16, 1, {ASM_AFF_ARGS}, ASM_AFF_DESC, 2, 0, 1, 0},\
	{0, 0, 0, {0, 0, 0, 0}, 0, 0, 0, 0, 0}\
};
