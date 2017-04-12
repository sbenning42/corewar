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

int main()
{
	printf("%s\n", RED("red"));
	printf("%s\n", GREEN("green"));
	printf("%s\n", BLUE("blue"));
	printf("%s\n", YELLOW("yellow"));
	printf("%s\n", PINK("pink"));
	printf("%s\n", CYAN("cyan"));
	printf("%s\n", ORANGE("orange"));
	printf("%s\n", BRUN("brun"));
	printf("%s\n", SOMBRE("sombre"));
	printf("%s\n", CLAIR("clair"));

    return (0);
}
