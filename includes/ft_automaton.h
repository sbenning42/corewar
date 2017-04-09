#ifndef FT_AUTOMATON_H
# define FT_AUTOMATON_H

# define NFA_DM             0xfff

# define NFA_FINAL          0x1
# define NFA_IS_FINAL(X)    (X & NFA_FINAL)
# define NFA_SET_FINAL(X)   (X |= NFA_FINAL)
# define NFA_UNSET_FINAL(X) (X &= ~(NFA_FINAL))

# define NFA_DUMP_TE_I      0
# define NFA_DUMP_TE_FN     "\t\t%{'%c'-'%c' : %.3p}\n"
# define NFA_DP_TE_1_FC     "\t\t%{'{yellow}%c{eoc}'-'{pink}%c{eoc}'"
# define NFA_DP_TE_2_FC     " : {cyan}%.3p{eoc}}\n"
# define NFA_DUMP_TE_FC     NFA_DP_TE_1_FC NFA_DP_TE_2_FC
# define NFA_DUMP_ETE_I     2
# define NFA_DUMP_ETE_FN    "\t\t%p\n"
# define NFA_DUMP_ETE_FC    "\t\t{cyan}%.3p{eoc}\n"
# define NFA_DUMP_SS_I      4
# define NFA_DUMP_SS_FN     "\t%s State %.3p:\n"
# define NFA_DUMP_SS_FC     "\t{yellow}%s{eoc} State {gr|cyan}%.3p{eoc}:\n"
# define NFA_DUMP_ST_I      6
# define NFA_DUMP_ST_FN     "\t\tTransition:\n"
# define NFA_DUMP_ST_FC     "\t\tTransition:\n"
# define NFA_DUMP_SET_I     8
# define NFA_DUMP_SET_FN    "\t\tEpsilone Transition:\n"
# define NFA_DUMP_SET_FC    "\t\tEpsilone Transition:\n"
# define NFA_DUMP_ND_I      10
# define NFA_DUMP_ND_FN     "No nfa to dump. . .\n"
# define NFA_DUMP_ND_FC     "{red}No nfa{eoc} to dump. . .\n"
# define NFA_DUMP_NDA_I     12
# define NFA_DP_NDA_1_FN    "Non determinist Finit Automaton (NFA):\nnb_state: "
# define NFA_DP_NDA_2_FN    "%d\nInitial State: %.3p\nFinal state: %.3p\n"
# define NFA_DUMP_NDA_FN    NFA_DP_NDA_1_FN NFA_DP_NDA_2_FN
# define NFA_DP_NDA_1_FC    "{gr}Non determinist Finit Automaton (NFA):{eoc}"
# define NFA_DP_NDA_2_FC    "\nnb_state: {gr|blue}%d{eoc}\nInitial State: "
# define NFA_DP_NDA_3_FC    "{gr|green}%.3p{eoc}\nFinal state: {red|gr}%.3p{eoc}\n"
# define NFA_DUMP_NDA_FC    NFA_DP_NDA_1_FC NFA_DP_NDA_2_FC NFA_DP_NDA_3_FC

# define NFA_R(X, Y)        nfa_range(X, Y)
# define NFA_A(X)           NFA_R(X, X)
# define NFA_J              nfa_joker()
# define NFA_E              nfa_epsilon()
# define NFA_KI(X)          nfa_kleen_point(X)
# define NFA_KP(X)          nfa_kleen_plus(X)
# define NFA_KS(X)          nfa_kleen_star(X)
# define NFA_DI(X, Y)       nfa_disjonction(X, Y)
# define NFA_CO(X, Y)       nfa_conjonction(X, Y)

#define REX_VAL_TYPE        1
#define REX_OP_TYPE         -1

#define REX_CHARS           "([)]?+*-|."
# define REX_POPEN_CODE     -'('
# define REX_BOPEN_CODE     -'['
# define REX_PCLOSE_CODE    -')'
# define REX_BCLOSE_CODE    -']'
# define REX_KPOINT_CODE    -'?'
# define REX_KPLUS_CODE     -'+'
# define REX_KSTAR_CODE     -'*'
# define REX_RANGE_CODE     -'-'
# define REX_CONJ_CODE      -'&'
# define REX_DISJ_CODE      -'|'
# define REX_POINT_CODE     -'.'

# include                   "libft.h"

typedef struct s_trans      t_trans;
typedef struct s_state      t_state;
typedef struct s_nfa        t_nfa;
typedef struct s_re_entry   t_re_entry;
typedef void                (*t_func)(char **, t_list **, int *);

struct                      s_trans
{
    char                    start;
    char                    end;
    t_state                 *state;
};

struct                      s_state
{
    int                     final;
    t_list                  *trans;
    t_list                  *eps_trans;
};

struct                      s_nfa
{
    t_list                  *state;
    t_state                 *initial;
    t_state                 *terminal;
    int                     nb_state;
};

struct                      s_re_entry
{
    int                     type;
    char                    c;
};

/*
**************************  INTERNE  *******************************************
*/

/*
**                          nfa_new.c
*/

t_list                      *nfa_new_trans_entry\
                                (char start, char end, t_state *state);
t_list                      *nfa_new_eps_trans_entry(t_state *state);
t_state                     *nfa_new_state\
                                (int final, t_list *trans, t_list *eps_trans);
t_nfa                       *nfa_new(void);
t_nfa                       *nfa_new_atom(void);
void                        nfa_merge(t_nfa *dest, t_nfa *origin);

/*
**                          nfa_add.c
*/

int                         nfa_add_trans_entry(t_list **trans, t_list *entry);
int                         nfa_add_eps_trans_entry\
                                (t_list **eps_trans, t_list *entry);
int                         nfa_add_trans(t_state *state, t_list *trans);
int                         nfa_add_eps_trans\
                                (t_state *state, t_list *aps_trans);
int                         nfa_add_state(t_nfa *nfa, t_state *state);

/*
**                          nfa_set.c
*/

void                        nfa_toggle_final_state(t_state *state);
void                        nfa_set_initial(t_nfa *nfa, t_state *state);
void                        nfa_set_terminal(t_nfa *nfa, t_state *state);

/*
**                          nfa_trans.c
*/

int                         nfa_trans\
                                (t_state *from, t_state *to,\
                                 char start, char end);
int                         nfa_eps_trans(t_state *from, t_state *to);

/*
**                          nfa_dump.c
*/

void                        nfa_dump_trans_entry(t_list *l, int color);
void                        nfa_dump_eps_trans_entry(t_list *l, int color);
void                        nfa_dump_trans(t_list *l, int color);
void                        nfa_dump_eps_trans(t_list *l, int color);
void                        nfa_dump_state(t_state *state, int color);
void                        nfa_dump_all_state(t_list *state, int color);

/*
**                          nfa_eval.c
*/

void                        nfa_eval_tokens\
                                (t_list **tokens, char *scan);
int                         nfa_eval_tokens_step\
                                (t_nfa *nfa, t_list **tokens,\
                                 char *scan, int size, int *max);
void                        nfa_clone_tokens(t_list **tokens);

/*
**                          regex_explicit.c
*/

t_list                      *regex2explicit(char *regex);
void                        regex_explicit_dump(t_list *stack);

/*
**                          explicit_rpn.c
*/

t_list                      *explicit2rpn(t_list *exp);
void                        rpn_dump(t_list *rpn);

/*
**                          rpn_nfa.c
*/

t_nfa                       *rpn2nfa(t_list *rpn);

/*
**                          nfa_del.c
*/

void                        nfa_l_del(void *c, size_t s);
void                        nfa_state_del(void *content, size_t size);
void                        nfa_all_state_del(t_list **l);
void                        nfa_del(t_nfa **nfa);
void                        nfa_deep_del(t_nfa **nfa);

/*
**************************  USER  **********************************************
*/

/*
**                          nfa_atom_preset.c
*/

t_nfa                       *nfa_atom(char c);
t_nfa                       *nfa_joker(void);
t_nfa                       *nfa_epsilon(void);
t_nfa                       *nfa_range(char start, char end);

/*
**                          nfa_kleen_preset.c
*/

t_nfa                       *nfa_kleen_star(t_nfa *origin);
t_nfa                       *nfa_kleen_plus(t_nfa *origin);
t_nfa                       *nfa_kleen_point(t_nfa *origin);

/*
**                          nfa_preset.c
*/

t_nfa                       *nfa_conjonction(t_nfa *left, t_nfa *right);
t_nfa                       *nfa_disjonction(t_nfa *left, t_nfa *right);
//t_nfa                     *nfa_negation(t_nfa *origin);

/*
**                          nfa.c
*/

t_nfa                       *nfa_regex2nfa(char *regex);
int                         nfa_is_terminal(t_nfa *nfa, t_list *tokens);
int                         nfa_match(t_nfa *nfa, char *scan);
int                         nfa_match_all(t_nfa *nfa, char *scan);

/*
**************************  DEBUG  *********************************************
*/

void                        nfa_dump(t_nfa *nfa, int color);

#endif
