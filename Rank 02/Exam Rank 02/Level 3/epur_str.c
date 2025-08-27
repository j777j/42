/*
Assignment name  : epur_str
Expected files   : epur_str.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string, and displays this string with exactly one
space between words, with no spaces or tabs either at the beginning or the end,
followed by a \n.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string.

If the number of arguments is not 1, or if there are no words to display, the
program displays \n.

Example:

$> ./epur_str "See? It's easy to print the same thing" | cat -e
See? It's easy to print the same thing$
$> ./epur_str " this        time it      will     be    more complex  . " | cat
	-e
this time it will be more complex .$
$> ./epur_str "No S*** Sherlock..." "nAw S*** ShErLaWQ..." | cat -e
$
$> ./epur_str "" | cat -e
$
$>
*/

#include <unistd.h>

int	main(int ac, char *av[])
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (ac == 2)
	{
		while (av[1][i] <= 32)
			i++;
		while (av[1][i])
		{
			if (av[1][i] <= 32)
				space = 1;
			else if (av[1][i] > 32)
			{
				if (space)
					write(1, " ", 1);
				write(1, &av[1][i], 1);
				space = 0;
			}
			i++;
		}
	}
	write(1, "\n", 1);
}

// #include <unistd.h> // For write

// void	ft_putchar(char c)
// {
// 	write(1, &c, 1);
// }

// void	epur_str(char *str)
// {
// 	int	idx;

// 	idx = 0;
// 	while (str[idx] == ' ' || str[idx] == '\t')
// 		idx++;
// 	while (str[idx] != '\0')
// 	{
// 		if (str[idx] == ' ' || str[idx] == '\t')
// 		{
// 			if (str[idx + 1] > ' ' && str[idx + 1] != '\0')
// 				ft_putchar(' ');
// 		}
// 		else if (str[idx] != ' ' && str[idx] != '\t')
// 			ft_putchar(str[idx]);
// 		idx++;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	if (argc == 2)
// 		epur_str(argv[1]);
// 	ft_putchar('\n');
// 	return (0);
// }

/*
#include <unistd.h> // For write

int	main(int argc, char const *argv[])
{
	int	i;
	int	flg;

	if (argc == 2)
	{
		i = 0;
		while (argv[1][i] == ' ' || argv[1][i] == '\t')
			i += 1;
		while (argv[1][i])
		{
			if (argv[1][i] == ' ' || argv[1][i] == '\t')
				flg = 1;
			if (!(argv[1][i] == ' ' || argv[1][i] == '\t'))
			{
				if (flg)
					write(1, " ", 1);
				flg = 0;
				write(1, &argv[1][i], 1);
			}
			i += 1;
		}
	}
	write(1, "\n", 1);
	return (0);
}
*/
