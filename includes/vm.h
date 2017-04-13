/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenning <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 10:51:41 by sbenning          #+#    #+#             */
/*   Updated: 2017/04/13 15:58:27 by sbenning         ###   ########.fr       */
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

# define MASK_1 (0xff000000)
# define MASK_2 (0xff0000)
# define MASK_3 (0xff00)
# define MASK_4 (0xff)

# define SHORT_FIRST(X) ((X & MASK_3) >> 0x8)
# define SHORT_SECOND(X) ((X & MASK_4) << 0x8)
# define SHORT_LITTLE2BIG(X) (SHORT_FIRST(X) + SHORT_SECOND(X))

# define INT_FIRST(X) ((X & MASK_1) >> 0x18)
# define INT_SECOND(X) ((X & MASK_2) >> 0x8)
# define INT_THIRD(X) ((X & MASK_3) << 0x8)
# define INT_FOURTH(X) ((X & MASK_4) << 0x18)
# define INT_COUPLE_FIRST(X) (INT_FIRST(X) + INT_SECOND(X))
# define INT_COUPLE_SECOND(X) (INT_THIRD(X) + INT_FOURTH(X))
# define INT_LITTLE2BIG(X) (INT_COUPLE_FIRST(X) + INT_COUPLE_SECOND(X))

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

/*
********************************************************************************
*/

/*
**								struct
*/

struct							s_vm_gconf
{
    unsigned int				max_player;
    unsigned int				mem_size;
    unsigned int				champ_max_size;
    unsigned int				reg_number;
    unsigned int				reg_size;
    unsigned int				idx_mod;
    unsigned int				cycle_to_die;
    unsigned int				cycle_delta;
    unsigned int				max_checks;
    unsigned int				nbr_live;
};

struct							s_vm_conf
{
    unsigned int				cycle;
	unsigned int				nb_player;
	unsigned int				nb_check;
	unsigned int				nb_live;
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

struct							s_vm_opcode_h
{
	unsigned char				opcode;
	void						(*func)(t_vm *, t_process *);
};

struct                          s_player
{
    int							id;
    header_t					header;
    t_file                      *file;
	unsigned char				binary[CHAMP_MAX_SIZE];
	size_t						binary_size;
    unsigned char				*pc;
    char						*color;
};

struct                          s_process
{
	int							player_id;
    unsigned char				*pc;
    int                         registre[REG_NUMBER];
    unsigned int                carry;
    unsigned int				timer;
    unsigned int				live;
    int							dead;
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

void							vm_new_player(t_vm *vm, char *name, int id);

/*
********************************************************************************
*/

/*
**								vm_load_process.c
*/

void							vm_load_process(t_vm *vm);
void							vm_put_memory(t_vm *vm);

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

void							vm_handler_opcode_live(t_vm *vm, t_process *p);
void							vm_handler_opcode_add(t_vm *vm, t_process *p);
void							vm_handler_opcode_sub(t_vm *vm, t_process *p);
void							vm_handler_opcode_aff(t_vm *vm, t_process *p);
void							vm_handler_opcode_zjmp(t_vm *vm, t_process *p);

/*
********************************************************************************
*/

/*
**								vm_handler_opcode_second_set.c
*/

void							vm_handler_opcode_and(t_vm *vm, t_process *p);
void							vm_handler_opcode_or(t_vm *vm, t_process *p);
void							vm_handler_opcode_xor(t_vm *vm, t_process *p);

/*
********************************************************************************
*/

/*
**								vm_handler_opcode_third_set.c
*/

void							vm_handler_opcode_ld(t_vm *vm, t_process *p);
void							vm_handler_opcode_st(t_vm *vm, t_process *p);
void							vm_handler_opcode_ldi(t_vm *vm, t_process *p);
void							vm_handler_opcode_sti(t_vm *vm, t_process *p);
void							vm_handler_opcode_fork(t_vm *vm, t_process *p);

/*
********************************************************************************
*/

/*
**								vm_handler_opcode_fourth_set.c
*/

void							vm_handler_opcode_lld(t_vm *vm, t_process *p);
void							vm_handler_opcode_lldi(t_vm *vm, t_process *p);
void							vm_handler_opcode_lfork(t_vm *vm, t_process *p);

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
**								vm_get.c
*/

int								vm_get_direct_int_arg(unsigned char *pc);
char							*vm_get_player_name(t_vm *vm, int id);

/*
********************************************************************************
*/

/*
**								vm_set.c
*/

void							vm_set_timer(t_process *p);

/*
********************************************************************************
*/

/*
**								vm_declare.c
*/

void							vm_declare_live(t_vm *vm, int id);

/*
********************************************************************************
*/

/*############################################################################*/
/*############################################################################*/
/*############################################################################*/
/*
# define VM_SINGLE              s_vm()

# define VM_A_CONFIG            VM_SINGLE->config
# define VM_A_MEMORY            VM_SINGLE->memory
# define VM_A_PLAYER            VM_SINGLE->player
# define VM_A_PROCESS           VM_SINGLE->process

# define VM_MNOTEXEC            "... is not a corewar executable."
# define VM_MPNUSED             "prog_number ... already used."
# define VM_MNOTACCESS          "File ... not accessible."
# define VM_MMALLOC             "Can't perform malloc."
# define VM_MUSAGE              "Usage: TODO (in vm.h, define VM_MUSAGE)"

# define VM_MLIVE               "le joueur %u(%s) est en vie.\n"
# define VM_MWIN                "le joueur %u(%s) a gagne.\n"
# define VM_MDEAD               "Un process appartenant au joueur %u(%s) est mort.\n"

# define VM_CONFIG1            "%30s : %lu\n%30s : %u\n%30s : %u\n%30s : %lu\n"
# define VM_CONFIG2            "%30s : %lu\n%30s : %u\n%30s : %u\n%30s : %u\n"
# define VM_CONFIG3            "%30s : %lu\n%30s : %u\n%30s : %u\n%30s : %lu\n"
# define VM_CONFIG4            "%30s : %u\n%30s : %lu\n%30s : %d(%s)\n%30s : %d\n%s"
# define VM_CONFIG_DUMP         VM_CONFIG1 VM_CONFIG2 VM_CONFIG3 VM_CONFIG4

# define VM_MEM1                "%30s : %p\n%30s : %p\n%30s : %p\n"
# define VM_MEM2                "%30s : %lu\n%30s : %lu\n%30s : %lu\n"
# define VM_MEMORY_DUMP         VM_MEM1 VM_MEM2

# define VM_PLAY1               "\t%30s : %d\n\t%30s : %s\n\t%30s : %ld\n"
# define VM_PLAY2               "\t%30s : %p\n\t%30s : %s\n\t%30s : %s\n"
# define VM_PLAYER_DUMP         VM_PLAY1 VM_PLAY2

# define VM_PROC1               "\t%30s : %u\n\t%30s : %p\n\t%30s : %p\n\t%30s : %p\n"
# define VM_PROC2               "\t%30s : %u\n\t%30s : %u\n\t%30s : %u\n"
# define VM_PROC3               "\t%30s : %lu\n\t%30s : %d\n\t%30s : %p\n"
# define VM_PROC4               "\t%30s : %p\n\t%30s : %u\n\t%30s : %lu\n"
# define VM_PROCESS_DUMP        VM_PROC1 VM_PROC2 VM_PROC3 VM_PROC4

# define VM_HEAD1               "\t%30s : %#x\n\t%30s : %s\n"
# define VM_HEAD2               "\t%30s : %u\n\t%30s : %s\n"
# define VM_HEADER_DUMP         VM_HEAD1 VM_HEAD2

# include                       "op.h"
# include                       "get_next_line.h"
# include                       "proginfo.h"
# include                       "ft_getopt.h"
# include                       "ft_file.h"
# include                       "libft.h"
# include                       "vm_vverbose.h"

typedef struct s_vm             t_vm;
typedef struct s_vm_config      t_vm_config;
typedef struct s_cbuff          t_cbuff;
typedef struct s_process        t_process;
typedef struct s_instruction    t_instruction;
typedef struct s_player         t_player;
typedef struct s_argd           t_argd;
typedef struct s_efatal         t_efatal;

typedef void                    (*t_arg_f)(char *);
typedef void                    (*t_ins_player)(t_process *);

struct                          s_instruction
{
    unsigned char               *code;
    unsigned int                size;
    t_op                        *op;
    unsigned char               ocp;
    unsigned char               *args;
};

struct                          s_cbuff
{
    void                        *buffer;
    void                        *end;
    void                        *curs;
    unsigned long               allocated_size;
    unsigned long               used_size;
    unsigned long               offset;
};


struct                          s_argd
{
    int                         type;
    t_arg_f                     f;
};

struct                          s_efatal
{
    int                         error;
    char                        *message;
};
*/
/*
**                              *** vm.c ***
*/
/*
t_vm                            *s_vm(void);
void                            vm_setup(void);
int                             vm_finish(void);
void                            vm_loop(void);
void                            vm_cleanup(void);
*/
/*
**                              *** vm_dump.c ***
*/
/*
void                            vm_dump(int fd);
*/
/*
**                              *** vm_dump_player.c ***
*/
/*
void                            vm_dump_player_i(t_list *l);
void							vm_put_players(void);
*/
/*
**                              *** vm_load.c ***
*/
/*
void                            vm_load_config(void);
void                            vm_load_arguments(void);
void                            vm_load_memory(void);
void                            vm_load_player(void);
void                            vm_load_root_process(void);
*/
/*
**                              *** vm_load_benary.c ***
*/
/*
void                            vm_load_binary(void);

t_arg_f                         arg_dispatch(int type);
void                            unknow_fatal(char *value);

void                            arg_error_f(char *value);
void                            arg_dump_f(char *value);
void                            arg_pnum_f(char *value);
void                            arg_oopt_f(char *value);
void                            arg_param_f(char *value);

void                            vm_create_player(char *file_name, int id);

int                             cbuff_init\
                                    (t_cbuff *cb, size_t size, size_t offset);
void                            cbuff_cpy(t_cbuff *cb, void *src, size_t size);
void                            cbuff_del(t_cbuff *cb);

void                            vm_load_player_i(t_list *l);

void                            vm_load_process_i(t_list *l);

void							vm_play_process(t_list *l);
void							vm_read_instruction(t_process *p);

t_ins_player					vm_player_dispatch(unsigned int opcode);

char							*vm_get_player_name(int id);

int                             vm_error(int error);
void                            vm_fatal(int fatal);

void                            vm_del_player(void *content, size_t size);
void                            vm_del_process(void *content, size_t size);

void                            ft_print_memory(void *m, size_t size);
void                            ft_print_legit_memory(void *m, size_t size);
void                            vm_print_memory(void *m, size_t s, char *c, int rel);

void							vm_declare_winner(void);
void							vm_declare_live(void);
void							vm_declare_dead(t_process *p);


int								vm_finish_dump(void);
int								vm_finish_live(void);
*/
#endif
