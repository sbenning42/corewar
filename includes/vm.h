/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:51:41 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/20 16:01:55 by sbenning         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
**								define
*/

# define VM_ERR_ARG             -1
# define VM_AFF_ARG            	0
# define VM_DUMP_ARG            1
# define VM_STEP_ARG            2
# define VM_PNUM_ARG            3
# define VM_VERB_ARG			4
# define VM_NUMBER_ARG          5
# define VM_CHAMP_ARG           6

# define VM_EUSAGE              -1
# define VM_EMALLOC             -2

# define VM_LIVE_VERB			0x1
# define VM_CYCLE_VERB			0x2
# define VM_OP_VERB				0x4
# define VM_DEATH_VERB			0x8
# define VM_PC_VERB				0x10

# define ISBIT(X, Y)			(X & Y)

# define VM_1U					"Usage: ./corewar [-d N -s N -v N | -b] "
# define VM_2U					"[-a] [-n N] <champion1.cor> [[-n N] <...>]\n"
# define VM_3U					"\t-a\t: Prints output from \"aff\" "
# define VM_4U					"(Default is to hide it)\n"
# define VM_5U					"#### TEXT OUTPUT MODE ########################"
# define VM_6U					"##################################\n"
# define VM_7U					"\t-d N\t: Dumps memory "
# define VM_C1U					VM_1U VM_2U VM_3U VM_4U VM_5U VM_6U VM_7U
# define VM_8U					"after N cycles then exits\n"
# define VM_9U					"\t-s N\t: Run N cycles, "
# define VM_10U					"dumps memory, pauses, then repeats\n"
# define VM_11U					"\t-v N\t: Verbosity levels, can be added "
# define VM_12U					"together to enable several\n"
# define VM_13U					"\t\t\t- 0 : Show only essentials\n"
# define VM_14U					"\t\t\t- 1 : Show lives\n"
# define VM_C2U					VM_8U VM_9U VM_10U VM_11U VM_12U VM_13U VM_14U
# define VM_15U					"\t\t\t- 2 : Show cycles\n"
# define VM_16U					"\t\t\t- 4 : Show operations "
# define VM_17U					"(Params are NOT lietteral ...)\n"
# define VM_18U					"\t\t\t- 8 : Show death\n"
# define VM_19U					"\t\t\t- 16 : Show PC movements "
# define VM_20U					"(Except for jumps)\n"
# define VM_C3U					VM_15U VM_16U VM_17U VM_18U VM_19U VM_20U
# define VM_MUSAGE				VM_C1U VM_C2U VM_C3U

# define MASK_1					(0xff000000)
# define MASK_2					(0xff0000)
# define MASK_3					(0xff00)
# define MASK_4					(0xff)

# define SHORT_FIRST(X)			((X & MASK_3) >> 0x8)
# define SHORT_SECOND(X)		((X & MASK_4) << 0x8)

# define SHORT_LITTLE2BIG(X)	(SHORT_FIRST(X) + SHORT_SECOND(X))

# define INT_FIRST(X)			((X & MASK_1) >> 0x18)
# define INT_SECOND(X)			((X & MASK_2) >> 0x8)
# define INT_THIRD(X)			((X & MASK_3) << 0x8)
# define INT_FOURTH(X)			((X & MASK_4) << 0x18)

# define INT_COUPLE_FIRST(X)	(INT_FIRST(X) + INT_SECOND(X))
# define INT_COUPLE_SECOND(X)	(INT_THIRD(X) + INT_FOURTH(X))

# define INT_LITTLE2BIG(X)		(INT_COUPLE_FIRST(X) + INT_COUPLE_SECOND(X))

/*
********************************************************************************
*/

/*
**								include
*/

# include						"libft.h"
# include						"ft_lexer.h"
# include						"ft_file.h"
# include						"op.h"

/*
********************************************************************************
*/

/*
**								typedef
*/

typedef struct s_vmerror		t_vmerror;
typedef struct s_main			t_main;
typedef struct s_vm_gconf		t_vm_gconf;
typedef struct s_vm_conf		t_vm_conf;
typedef struct s_vm				t_vm;
typedef struct s_vm_args_h		t_vm_args_h;
typedef struct s_vm_opcode_h	t_vm_opcode_h;
typedef struct s_player			t_player;
typedef struct s_process		t_process;
typedef union u_swap			t_swap;
typedef enum e_e_insarg			t_e_insarg;
typedef struct s_insarg_i		t_insarg_i;
typedef struct s_instruction	t_instruction;


/*
********************************************************************************
*/

/*
**								struct
*/

struct							s_vm_gconf
{
    unsigned int				max_player;
    int						mem_size;
    int						champ_max_size;
    int						reg_number;
    int						reg_size;
   	int						idx_mod;
    int						cycle_to_die;
    int						cycle_delta;
    int						max_checks;
    long int				nbr_live;
};

struct							s_vm_conf
{
    long int					cycle;
    long int					cycle_tot;
	unsigned int				nb_player;
	int							nb_check;
	long int					nb_live;
    int							aff;
    int							dump;
    int							step;
    int							verb;
	int							last_live_id;
};

struct                          s_vm
{
    t_vm_gconf					gconfig;
    t_vm_conf					config;
    unsigned char				memory[MEM_SIZE];
    char						*color[MEM_SIZE];
    t_list						*player;
    t_list						*process;
};

struct							s_vmerror
{
	int							error;
	char						*message;
};

struct							s_main
{
	int							ac;
	char						**av;
};

struct							s_vm_args_h
{
	int							id;
	void						(*func)(t_vm *, char *);
};

union							u_swap
{
	char						u_char;
	short						u_short;
	int							u_int;
	char						u_tab[4];
};

enum							e_e_insarg
{
	reg_arg,
	dir_arg,
	ind_arg
};

struct							s_insarg_i
{
	t_e_insarg					type;
	int							value;
};

struct							s_instruction
{
	int							pc;
	unsigned char				op;
	unsigned char				ocp;
	t_insarg_i					args[4];
	int							nb_arg;
	int							size;
};

struct							s_vm_opcode_h
{
	unsigned char				opcode;
	void						(*func)(t_vm *, t_process *, t_instruction *);
};

struct                          s_player
{
    long int					id;
    header_t					header;
    t_file                      *file;
	unsigned char				binary[CHAMP_MAX_SIZE];
	size_t						binary_size;
    int							pc;
    char						*color;
};

struct                          s_process
{
	int							player_id;
	int							id;
    int							pc;
    int                         registre[REG_NUMBER + 1];
    unsigned int                carry;
    unsigned int				timer;
    long int					live;
    int							dead;
	unsigned char				opcode;
//	t_instruction				ins;
	char						*color;
};

/*
********************************************************************************
*/

/*
**								vm_error.c
*/

char							*vm_strerror(int error);
int								vm_error(int error);
void							vm_fatal(int error);
void							vm_error_notaccess(char *file);
void							vm_error_notcorewar(char *file);

/*
********************************************************************************
*/

/*
**								vm_main.c
*/

void							set_main(int ac, char **av);
int								main_ac(void);
char							**main_av(void);
char							*prog_name(void);

/*
********************************************************************************
*/

/*
**								vm_args.c
*/

void							set_args(char **k, char **re, size_t size);
t_lexem							*get_arg(void);
void							del_args(void);

/*
********************************************************************************
*/

/*
**								vm_setup.c
*/

void							vm_setup(t_vm *vm);

/*
********************************************************************************
*/

/*
**								vm_load_args.c
*/

void							vm_load_args(t_vm *vm);

/*
********************************************************************************
*/

/*
**								vm_handler_args.c
*/

void							vm_handler_arg_affiche(t_vm *vm, char *arg);
void							vm_handler_arg_dump(t_vm *vm, char *arg);
void							vm_handler_arg_step(t_vm *vm, char *arg);
void							vm_handler_arg_pnum(t_vm *vm, char *arg);
void							vm_handler_arg_verbose(t_vm *vm, char *arg);
void							vm_handler_arg_champion(t_vm *vm, char *arg);

/*
********************************************************************************
*/

/*
**								vm_new_player.c
*/

void							vm_new_player(t_vm *vm, char *name, long int id);
int								is_available_id(t_vm *vm, long int id);

/*
********************************************************************************
*/

/*
**								vm_load_process.c
*/

void							vm_put_pc_move(t_vm *vm, int pc_start, int offset, t_instruction *ins);
void							vm_load_process(t_vm *vm);
void							vm_put_memory(t_vm *vm);
void							vm_put_players(t_vm *vm);
void							vm_new_process(t_vm *vm, int pc, long int id, char *color);
void							vm_new_fprocess(t_vm *vm, int pc, t_process *p);

/*
********************************************************************************
*/

/*
**								vm_play_process.c
*/

void							vm_play_process(t_vm *vm);

/*
********************************************************************************
*/

/*
**								vm_handler_opcode_first_set.c
*/

void							vm_handler_opcode_live(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_add(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_sub(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_aff(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_zjmp(t_vm *vm, t_process *p, t_instruction *ins);

/*
********************************************************************************
*/

/*
**								vm_handler_opcode_second_set.c
*/

void							vm_handler_opcode_and(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_or(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_xor(t_vm *vm, t_process *p, t_instruction *ins);

/*
********************************************************************************
*/

/*
**								vm_handler_opcode_third_set.c
*/

void							vm_handler_opcode_ld(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_st(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_ldi(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_sti(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_fork(t_vm *vm, t_process *p, t_instruction *ins);

/*
********************************************************************************
*/

/*
**								vm_handler_opcode_fourth_set.c
*/

void							vm_handler_opcode_lld(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_lldi(t_vm *vm, t_process *p, t_instruction *ins);
void							vm_handler_opcode_lfork(t_vm *vm, t_process *p, t_instruction *ins);

/*
********************************************************************************
*/

/*
**								vm_check.c
*/

void							vm_check_process(t_vm *vm);
void							vm_check_live(t_vm *vm);
void							vm_check_checks(t_vm *vm);

/*
********************************************************************************
*/

/*
**								vm_check_rules.c
*/

int								vm_check_dump(t_vm *vm);
void							vm_check_step(t_vm *vm);
int								vm_check_cycle(t_vm *vm);

/*
********************************************************************************
*/

/*
**								vm_del.c
*/

void							vm_del_player(void *content, size_t size);
void							vm_del_process(void *content, size_t size);

/*
********************************************************************************
*/

/*
**								vm_is.c
*/

int								vm_is_process_dead\
									(void *ref, void *c, size_t size);

/*
********************************************************************************
*/

/*
**								vm_set.c
*/

void							vm_set_timer(t_vm *vm, t_process *p);

/*
********************************************************************************
*/

/*
**								vm_declare.c
*/

void							vm_declare_cycle(t_vm *vm);
void							vm_declare_live(t_vm *vm, long int id);
void							vm_declare_win(t_vm *vm);

/*
********************************************************************************
*/

/*
**								vm_put_instruction.c
*/

void							vm_put_instruction(t_vm *vm, t_process *p, t_instruction *ins);

/*
********************************************************************************
*/

/*
**								vm_access.c
*/

unsigned char					bin_access(t_vm *vm, int pc);
void							vm_read_instruction(t_vm *vm, int pc, t_instruction *ins, unsigned char opcode);
int								access_arg_value(t_insarg_i *arg, t_vm *vm, t_process *p, int *err);
void							write_int(t_vm *vm, int *pc, int value);
int								read_int(t_vm *vm, int *pc);
int								vm_pc(t_vm *vm, int pc);
int								check_reg_index(t_vm *vm, int i);

/*
********************************************************************************
*/

char				*vm_get_player_name(t_vm *vm, int id);
#endif
