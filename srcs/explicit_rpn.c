#include "ft_automaton.h"

t_re_entry      pop_stack(t_list **stack)
{
    t_re_entry  re;
    t_list      *t;

    re.c = 0;
    re.type = 0;
    if (!*stack)
        return (re);
    t = (*stack)->next;
    (*stack)->next = NULL;
    re = *(t_re_entry *)(*stack)->content;
    ft_lstdel(stack, nfa_l_del);
    *stack = t;
    return (re);
}

t_re_entry      eval_stack(t_list *stack)
{
    t_re_entry  re;

    re.c = 0;
    re.type = 0;
    if (!stack)
        return (re);
    return (*(t_re_entry *)stack->content);
}

void            push_stack(t_list **stack, t_re_entry re)
{
    t_list      *l;

    if (!(l = ft_lstnew(&re, sizeof(t_re_entry))))
        return ;
    ft_lstadd(stack, l);
}

void            push_rpn(t_list **rpn, t_re_entry re)
{
    t_list      *l;

    if (!(l = ft_lstnew(&re, sizeof(t_re_entry))))
        return ;
    ft_lstadd_back(rpn, l);
}

void            rpn_handler_val(t_list **rpn, t_list **stack, t_list *exp)
{
    push_rpn(rpn, *(t_re_entry *)exp->content);
    (void)stack;
}

void            rpn_handler_bpclose(t_list **rpn, t_list **stack, t_list *exp)
{
    t_re_entry  re;

    if (!*stack)
        return ;
    while (42)
    {
        re = pop_stack(stack);
        if (re.c == REX_BOPEN_CODE || re.c == REX_POPEN_CODE)
            break ;
        push_rpn(rpn, re);
    }
    (void)exp;
}

t_re_entry      g_prior[] = {\
    {0, -'|'},\
    {1, -'&'},\
    {2, -'-'},\
    {3, -'*'},\
    {3, -'+'},\
    {3, -'?'},\
    {4, -'('},\
    {4, -'['},\
    {-1, 0}\
};

int             get_prior(t_re_entry r)
{
    int         i;

    i = -1;
    while (g_prior[++i].c)
    {
        if (r.c == g_prior[i].c)
            return (g_prior[i].type);
    }
    return (-1);
}

int             is_prior(t_re_entry r1, t_re_entry r2)
{
    return (get_prior(r1) > get_prior(r2));
}

void            rpn_handler_other_op(t_list **rpn, t_list **stack, t_list *exp)
{
    t_re_entry  re;

    while (42)
    {
        if (!*stack)
            break ;
        re = eval_stack(*stack);
        if (re.c == REX_BOPEN_CODE || re.c == REX_POPEN_CODE)
            break ;
        if (is_prior(*(t_re_entry *)exp->content, re))
            break ;
        re = pop_stack(stack);
        push_rpn(rpn, re);
    }
    push_stack(stack, *(t_re_entry *)exp->content);
}

void            rpn_handler_op(t_list **rpn, t_list **stack, t_list *exp)
{
    t_re_entry  *re;

    re = (t_re_entry *)exp->content;
    if (re->c == REX_PCLOSE_CODE || re->c == REX_BCLOSE_CODE)
        rpn_handler_bpclose(rpn, stack, exp);
    else
        rpn_handler_other_op(rpn, stack, exp);
}

void            rpn_handler(t_list **rpn, t_list **stack, t_list *exp)
{
    t_re_entry  *re;

    re = (t_re_entry *)exp->content;
    if (re->type == REX_VAL_TYPE || re->c == REX_POINT_CODE)
        rpn_handler_val(rpn, stack, exp);
    else if (re->type == REX_OP_TYPE)
        rpn_handler_op(rpn, stack, exp);
}

void            rec_explicit2rpn(t_list **rpn, t_list **stack, t_list *exp)
{
    if (!exp)
        return ;
    rpn_handler(rpn, stack, exp);
    rec_explicit2rpn(rpn, stack, exp->next);
}

t_list          *explicit2rpn(t_list *exp)
{
    t_list      *rpn;
    t_list      *stack;

    rpn = NULL;
    stack = NULL;
    rec_explicit2rpn(&rpn, &stack, exp);
    while (stack)
        push_rpn(&rpn, pop_stack(&stack));
    return (rpn);
}

void            rpn_dump(t_list *rpn)
{
    t_re_entry  *re;

    ft_printf("Rpn: ");
    while (rpn)
    {
        re = (t_re_entry *)rpn->content;
        if (re->type == REX_VAL_TYPE)
            ft_printf("%c", re->c);
        else if (re->type == REX_OP_TYPE)
            ft_printf("{gr}%c{eoc}", -re->c);
        rpn = rpn->next;
    }
    ft_printf("\n");
}
