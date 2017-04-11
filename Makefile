#* ************************************************************************** *#
#*                                                                            *#
#*                                                        :::      ::::::::   *#
#*   Makefile                                           :+:      :+:    :+:   *#
#*                                                    +:+ +:+         +:+     *#
#*   By: sbenning <sbenning@student.42.fr>          +#+  +:+       +#+        *#
#*                                                +#+#+#+#+#+   +#+           *#
#*   Created: 2015/12/18 23:33:22 by sbenning          #+#    #+#             *#
#*   Updated: 2017/03/09 15:07:24 by sbenning         ###   ########.fr       *#
#*                                                                            *#
#* ************************************************************************** *#

NAME =			vm

SRC =			main.c\
                ft_file.c\
                ft_print_memory.c\
                ft_gen_lex.c\
                ft_getopt.c\
                ft_lexer.c\
                ft_smart_getopt.c\
                get_next_line.c\
                nfa_add.c\
                nfa_atom_preset.c\
                nfa.c\
                nfa_del.c\
                nfa_dump.c\
                nfa_eval.c\
                nfa_kleen_preset.c\
                nfa_new.c\
                nfa_preset.c\
                nfa_set.c\
                nfa_trans.c\
                op.c\
                proginfo.c\
                regex_explicit.c\
                explicit_rpn.c\
                rpn_nfa.c\
                lexer_del.c\
                vm.c\
                vm_dump.c\
                vm_dump_player.c\
                vm_load.c\
                vm_load_binary.c\
                vm_load_arguments.c\
                vm_load_arguments_f.c\
                vm_create_player.c\
                vm_cbuff.c\
                vm_load_player.c\
                vm_load_process.c\
                vm_play_process.c\
                vm_fatal.c\
                vm_del.c\
                vm_print_memory.c\
                vm_vverbose.c

SRC_DIR =		srcs/
OBJ_DIR =		obj/

OBJ =			$(SRC:.c=.o)

COR_SRC =		$(addprefix $(SRC_DIR), %.c)

COR_OBJ =		$(addprefix $(OBJ_DIR), %.o)

ABS_OBJ =		$(addprefix $(OBJ_DIR), $(OBJ))

HEADER =		includes

DEPEND =	    vm.h

ABS_DEPEND =	$(addprefix $(HEADER)/, $(DEPEND))

LIBFT =			ft

OBJ_LIBFT =		libft.a

LIBFT_DIR =		libft

ABS_OBJ_LIBFT =	$(addprefix $(LIBFT_DIR)/, $(OBJ_LIBFT))

LIBFT_HEADER =	$(addprefix $(LIBFT_DIR)/, $(HEADER))

CC =			gcc

FLAG =			-Wall -Wextra -Werror

all : $(ABS_OBJ_LIBFT) $(NAME)

$(NAME) : $(ABS_OBJ)
	$(CC) $(FLAG) -g -o $@ $^ -L$(LIBFT_DIR) -l$(LIBFT)

$(COR_OBJ) : $(COR_SRC) $(ABS_DEPEND)
	$(CC) $(FLAG) -g -o $@ -c $< -I$(HEADER) -I$(LIBFT_HEADER)

$(ABS_OBJ_LIBFT) :
	make -C $(LIBFT_DIR)

lclean :
	make clean -C $(LIBFT_DIR)

lfclean :
	make fclean -C $(LIBFT_DIR)

lre : 
	make re -C $(LIBFT_DIR)

clean :
	rm -f $(ABS_OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all

