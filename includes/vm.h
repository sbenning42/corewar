#ifndef VM_H
# define VM_H

# define VM_OPT_CHARSET         "vVs"

# define VM_VERBOSE_OPT         0x1
# define VM_VVERBOSE_OPT        0x2
# define VM_SERIAL_OPT          0x4

# define VM_ARG_ERR             -1
# define VM_ARG_DUMP            0
# define VM_ARG_PNUM            1
# define VM_ARG_OOPT            2
# define VM_ARG_PARAM           3

# define VM_ENOTEXEC            -1
# define VM_EPNUSED             -2
# define VM_ENOTACCESS          -3
# define VM_EMALLOC             -4
# define VM_EUSAGE              -5

# define MASK_1 (0xff << 0x18)
# define MASK_2 (0xff << 0x10)
# define MASK_3 (0xff << 0x8)
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

# define VM_MLIVE               "le joueur %u(%s) est en vie."
# define VM_MWIN                "le joueur %u(%s) a gagne."

# define VM_CONFIG1            "%30s : %lu\n%30s : %u\n%30s : %u\n%30s : %lu\n"
# define VM_CONFIG2            "%30s : %lu\n%30s : %u\n%30s : %u\n%30s : %u\n"
# define VM_CONFIG3            "%30s : %lu\n%30s : %u\n%30s : %u\n%30s : %lu\n"
# define VM_CONFIG4            "%30s : %u\n%30s : %lu\n%30s : %d(%s)\n%30s : %d\n%s"
# define VM_CONFIG_DUMP         VM_CONFIG1 VM_CONFIG2 VM_CONFIG3 VM_CONFIG4

# define VM_MEM1                "%30s : %p\n%30s : %p\n%30s : %p\n"
# define VM_MEM2                "%30s : %lu\n%30s : %lu\n%30s : %lu\n"
# define VM_MEMORY_DUMP         VM_MEM1 VM_MEM2

# define VM_PLAY1               "\t%30s : %d\n"
# define VM_PLAY2               "\t%30s : %s\n\t%30s : %ld\n\t%30s : %p\n"
# define VM_PLAYER_DUMP         VM_PLAY1 VM_PLAY2

# define VM_PROC1               "\t%30s : %u\n\t%30s : %p\n\t%30s : %p\n"
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

struct                          s_instruction
{
    unsigned char               *code;
    unsigned int                size;
    t_op                        *op;
    unsigned char               ocp;
    unsigned char               *args;
};

struct                          s_process
{
    pid_t                       pid;
    void                        *pc;
    int                         registre[REG_NUMBER];
    unsigned int                reg_number;
    unsigned int                reg_size;
    unsigned int                carry;
    unsigned long               timer;
    int                         error;
    t_instruction               *instruction;
    unsigned char               *last_instruction;
    unsigned int                size_instruction;
    unsigned long               tic;
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

struct                          s_player
{
    int                         id;
    header_t                    header;
    t_file                      *obj_file;
    long int                    live;
    void                        *pc;
};

struct                          s_vm_config
{
    unsigned int                nb_player;
    unsigned int                max_player;
    unsigned int                max_process;
    unsigned long               mode;
    unsigned long               mem_size;
    unsigned long               max_player_size;
    unsigned int                reg_number;
    unsigned int                reg_size;
    unsigned long               idx_mod;
    unsigned int                cycle_to_die;
    unsigned int                cycle_delta;
    unsigned int                max_checks;
    unsigned long               nbr_live;
    unsigned long               nbr_live_check;
    int                         id_last_live;
    char                        *name_last_live;
    int                         dump;
};

struct                          s_vm
{
    t_vm_config                 config;
    t_cbuff                     memory;
    t_list                      *player;
    t_list                      *process;
    unsigned long               tic;
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


/*
**                              *** vm.c ***
*/

t_vm                            *s_vm(void);
void                            vm_setup(void);
int                             vm_finish(void);
void                            vm_loop(void);
void                            vm_cleanup(void);

/*
**                              *** vm_dump.c ***
*/

void                            vm_dump(int fd);

/*
**                              *** vm_dump_player.c ***
*/

void                            vm_dump_player_i(t_list *l);
void							vm_put_players(void);

/*
**                              *** vm_load.c ***
*/

void                            vm_load_config(void);
void                            vm_load_arguments(void);
void                            vm_load_memory(void);
void                            vm_load_player(void);
void                            vm_load_root_process(void);

/*
**                              *** vm_load_benary.c ***
*/

void                            vm_load_binary(void);

/*
**                              *** vm_load_arguments.c ***
*/

t_arg_f                         arg_dispatch(int type);
void                            unknow_fatal(char *value);

/*
**                              *** vm_load_arguments_f.c ***
*/

void                            arg_error_f(char *value);
void                            arg_dump_f(char *value);
void                            arg_pnum_f(char *value);
void                            arg_oopt_f(char *value);
void                            arg_param_f(char *value);

/*
**                              *** vm_create_player.c ***
*/

void                            vm_create_player(char *file_name, int id);

/*
**                              *** vm_cbuff.c ***
*/

int                             cbuff_init\
                                    (t_cbuff *cb, size_t size, size_t offset);
void                            cbuff_cpy(t_cbuff *cb, void *src, size_t size);
void                            cbuff_del(t_cbuff *cb);

/*
**                              *** vm_load_player.c ***
*/

void                            vm_load_player_i(t_list *l);

/*
**                              *** vm_load_process.c ***
*/

void                            vm_load_process_i(t_list *l);

/*
**                              *** vm_play_process.c ***
*/

void							vm_play_process(t_list *l);

/*
**                              *** vm_fatal.c ***
*/

int                             vm_error(int error);
void                            vm_fatal(int fatal);

/*
**                              *** vm_del.c ***
*/

void                            vm_del_player(void *content, size_t size);
void                            vm_del_process(void *content, size_t size);

void                            ft_print_memory(void *m, size_t size);
void                            ft_print_legit_memory(void *m, size_t size);

#endif
