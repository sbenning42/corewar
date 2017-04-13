#include <stdio.h>

# define COL(X, Y, Z, S)	"\033[38;2;"#X";"#Y";"#Z"m"S"\033[0m"
# define RED(S)				"\033[38;2;255;0;0m"S"\033[0m"
# define GREEN(S)			"\033[38;2;0;255;0m"S"\033[0m"
# define BLUE(S)			"\033[38;2;0;0;255m"S"\033[0m"
# define YELLOW(S)			"\033[38;2;255;255;0m"S"\033[0m"
# define PINK(S)			"\033[38;2;255;0;255m"S"\033[0m"
# define CYAN(S)			"\033[38;2;0;255;255m"S"\033[0m"
# define ORANGE(S)			"\033[38;2;237;127;16m"S"\033[0m"
# define BRUN(S)			"\033[38;2;91;60;17m"S"\033[0m"
# define SOMBRE(S)			"\033[38;2;63;34;4m"S"\033[0m"
# define CLAIR(S)			"\033[38;2;245;245;220m"S"\033[0m"


#define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define IIF(c) PRIMITIVE_CAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)
#define COMPL_0 1
#define COMPL_1 0

#define BITAND(x) PRIMITIVE_CAT(BITAND_, x)
#define BITAND_0(y) 0
#define BITAND_1(y) y

#define INC(x) PRIMITIVE_CAT(INC_, x)
#define INC_0 1
#define INC_1 2
#define INC_2 3
#define INC_3 4
#define INC_4 5
#define INC_5 6
#define INC_6 7
#define INC_7 8
#define INC_8 9
#define INC_9 9

#define DEC(x) PRIMITIVE_CAT(DEC_, x)
#define DEC_0 0
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2
#define DEC_4 3
#define DEC_5 4
#define DEC_6 5
#define DEC_7 6
#define DEC_8 7
#define DEC_9 8

#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0,)
#define PROBE(x) x, 1,

#define IS_PAREN(x) CHECK(IS_PAREN_PROBE x)
#define IS_PAREN_PROBE(...) PROBE(~)

#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))
#define NOT_0 PROBE(~)

#define BOOL(x) COMPL(NOT(x))
#define IF(c) IIF(BOOL(c))

#define EAT(...)
#define EXPAND(...) __VA_ARGS__
#define WHEN(c) IF(c)(EXPAND, EAT)

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(...) __VA_ARGS__ DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__

#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__

#define REPEAT(count, macro, ...) \
	    WHEN(count) \
    ( \
	          OBSTRUCT(REPEAT_INDIRECT) () \
	          ( \
				            DEC(count), macro, __VA_ARGS__ \
				        ) \
	          OBSTRUCT(macro) \
	          ( \
				            DEC(count), __VA_ARGS__ \
				        ) \
	      )
#define REPEAT_INDIRECT() REPEAT

#define M(i, _) i

int main()
{
	int q[] = {EVAL(REPEAT(8, M, ~))};
    return (0);
}
