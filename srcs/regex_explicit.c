#include "ft_automaton.h"

static void            push_stack(t_list **stack, int type, char c)
{
    t_list      *l;
    t_re_entry  re;

    re.type = type;
    re.c = c;
    if (!(l = ft_lstnew(&re, sizeof(t_re_entry))))
        return ;
    ft_lstadd_back(stack, l);
}

void            explicit_conjonction(t_list **stack, int *n)
{
    if (*n < 1)
        return ;
    push_stack(stack, REX_OP_TYPE, -'&');
    *n -= 1;
}

void            push_val(t_list **stack, int *n, char c)
{
    explicit_conjonction(stack, n);
    push_stack(stack, REX_VAL_TYPE, c);
    *n += 1;
}

void            push_op(t_list **stack, int *n, char c)
{
    explicit_conjonction(stack, n);
    push_stack(stack, REX_OP_TYPE, c);
    *n += 1;
}

void            esc_f(char **regex, t_list **stack, int *n)
{
    explicit_conjonction(stack, n);
    *regex += 1;
    if (!**regex)
        return ;
    push_stack(stack, REX_VAL_TYPE, **regex);
    *n += 1;
}

void            joker_f(char **regex, t_list **stack, int *n)
{
    push_op(stack, n, -'.');
    (void)regex;
}

void            op_f(char **regex, t_list **stack, int *n)
{
    if (**regex == '(' || **regex == '[')
        explicit_conjonction(stack, n);
    else if (**regex == '|' || **regex == '-')
        *n = 0;
    push_stack(stack, REX_OP_TYPE, -(**regex));
}

void            val_f(char **regex, t_list **stack, int *n)
{
    push_val(stack, n, **regex);
}

void            nop_f(char **regex, t_list **stack, int *n)
{
    (void)regex;
    (void)stack;
    (void)n;
}

int             dispatch(char c)
{
    if (c == '\\')
        return (0);
    else if (c == '.')
        return (1);
    else if (ft_strchr(REX_CHARS, c))
        return (2);
    else if (c != '&')
        return (3);
    return (4);
}

t_func          g_func[] = {\
    esc_f,\
    joker_f,\
    op_f,\
    val_f,\
    nop_f\
};

t_list          *regex2explicit(char *regex)
{
    t_list      *stack;
    int         n;

    stack = NULL;
    n = 0;
    while (*regex)
    {
        g_func[dispatch(*regex)](&regex, &stack, &n);
        ++regex;
    }
    return (stack);
}

void            regex_explicit_dump(t_list *stack)
{
    t_re_entry  *re;

    ft_printf("Explicit: ");
    while (stack)
    {
        re = (t_re_entry *)stack->content;
        if (re->type == REX_VAL_TYPE)
            ft_printf("%c", re->c);
        else if (re->type == REX_OP_TYPE)
            ft_printf("{gr}%c{eoc}", -re->c);
        stack = stack->next;
    }
    ft_printf("\n");
}
