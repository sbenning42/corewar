#include "ft_automaton.h"

typedef int             (*t_factor)(t_list **, t_re_entry *);
typedef struct s_disp   t_disp;

struct                  s_disp
{
    char                c;
    t_factor            f;
};

static t_nfa            *pop_stack(t_list **stack)
{
    t_list              *h;
    t_list              *t;
    t_nfa               *nfa;

    h = *stack;
    if (!h)
        return (NULL);
    t = h->next;
    *stack = t;
    h->next = NULL;
    nfa = *(t_nfa **)h->content;
    ft_lstdel(&h, nfa_l_del);
    return (nfa);
}

static t_nfa            *eval_stack(t_list *stack)
{
    if (!stack)
        return (NULL);
    return (*(t_nfa **)stack->content);
}

static int              push_stack(t_list **stack, t_nfa *nfa)
{
    t_list              *l;

    l = ft_lstnew(&nfa, sizeof(t_nfa *));
    if (!l)
        return (-1);
    ft_lstadd(stack, l);
    return (0);
}

static t_nfa                   *nfa_make_range(t_nfa *a1, t_nfa **a2)
{
    t_trans             *t1;
    t_trans             *t2;

    t1 = (t_trans *)a1->initial->trans->content;
    t2 = (t_trans *)(*a2)->initial->trans->content;
    t1->end = t2->start;
    nfa_deep_del(a2);
    return (a1);
}

static int                     range_f(t_list **stack, t_re_entry *rex)
{
    t_nfa               *left;
    t_nfa               *right;
    t_nfa               *nfa;

    if (!(eval_stack(*stack) && eval_stack((*stack)->next)))
        return (1);
    right = pop_stack(stack);
    left = pop_stack(stack);
    nfa = nfa_make_range(left, &right);
    push_stack(stack, nfa);
    return (0);
    (void)rex;
}

static int                     atom_f(t_list **stack, t_re_entry *rex)
{
    t_nfa               *nfa;

    if (!(nfa = nfa_atom(rex->c)))
        return (-1);
    return (push_stack(stack, nfa));
}

static int                     joker_f(t_list **stack, t_re_entry *rex)
{
    t_nfa               *nfa;

    if (!(nfa = nfa_joker()))
        return (-1);
    return (push_stack(stack, nfa));
    (void)rex;
}

static int              push_unary(t_list **stack, t_nfa *(*f)(t_nfa *))
{
    t_nfa               *origin;
    t_nfa               *nfa;

    if (!eval_stack(*stack))
        return (1);
    origin = pop_stack(stack);
    if (!(nfa = f(origin)))
        return (-1);
    return (push_stack(stack, nfa));
}

static int              push_binary(t_list **stack, t_nfa *(*f)(t_nfa *, t_nfa *))
{
    t_nfa               *left;
    t_nfa               *right;
    t_nfa               *nfa;

    if (!(eval_stack(*stack) && eval_stack((*stack)->next)))
        return (1);
    right = pop_stack(stack);
    left = pop_stack(stack);
    if (!(nfa = f(left, right)))
        return (-1);
    return (push_stack(stack, nfa));
}

static int                     kleen_point_f(t_list **stack, t_re_entry *rex)
{
    return (push_unary(stack, nfa_kleen_point));
    (void)rex;
}

static int                     kleen_plus_f(t_list **stack, t_re_entry *rex)
{
    return (push_unary(stack, nfa_kleen_plus));
    (void)rex;
}

static int                     kleen_star_f(t_list **stack, t_re_entry *rex)
{
    return (push_unary(stack, nfa_kleen_star));
    (void)rex;
}

static int                     conjonction_f(t_list **stack, t_re_entry *rex)
{
    return (push_binary(stack, nfa_conjonction));
    (void)rex;
}

static int                     disjonction_f(t_list **stack, t_re_entry *rex)
{
    return (push_binary(stack, nfa_disjonction));
    (void)rex;
}

t_disp                  g_dispatch[] = {\
    {REX_RANGE_CODE, range_f},\
    {REX_POINT_CODE, joker_f},\
    {REX_KPOINT_CODE, kleen_point_f},\
    {REX_KPLUS_CODE, kleen_plus_f},\
    {REX_KSTAR_CODE, kleen_star_f},\
    {REX_CONJ_CODE, conjonction_f},\
    {REX_DISJ_CODE, disjonction_f},\
    {0, NULL}\
};

static t_factor                dispatch(t_re_entry *rex)
{
    int                 i;

    i = -1;
    while (g_dispatch[++i].f)
    {
        if (g_dispatch[i].c == rex->c)
            return (g_dispatch[i].f);
    }
    return (atom_f);
}

static t_nfa                   *rec_rpn2nfa(t_list **stack, t_list *rpn)
{
    t_re_entry          *rex;

    if (!rpn)
        return (pop_stack(stack));
    rex = (t_re_entry *)rpn->content;
    if (dispatch(rex)(stack, rex))
        return (NULL);
    return (rec_rpn2nfa(stack, rpn->next));
}

t_nfa                   *rpn2nfa(t_list *rpn)
{
    t_list              *stack;

    stack = NULL;
    return (rec_rpn2nfa(&stack, rpn));
}
