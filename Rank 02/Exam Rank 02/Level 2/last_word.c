/*

Assignment name  : last_word
Expected files   : last_word.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes a string and displays its last word followed by a \n.

A word is a section of string delimited by spaces/tabs or by the start/end of
the string.

If the number of parameters is not 1, or there are no words, display a newline.

Example:

$> ./last_word "FOR PONY" | cat -e
PONY$
$> ./last_word "this        ...       is sparta, then again, maybe    not" | cat
	-e
not$
$> ./last_word "   " | cat -e
$
$> ./last_word "a" "b" | cat -e
$
$> ./last_word "  lorem,ipsum  " | cat -e
lorem,ipsum$
$>

*/

// // //this one below is also ok, I should learn about ii =-1 and ++i;
// #include <unistd.h>

// int	main(int ac, char **av)
// {
// 	int	i;
// 	int	j;

// 	if (ac == 2)
// 	{
// 		i = -1;
// 		j = 0;
// 		while (av[1][++i])
// 		{
// 			if (av[1][i] == 32 && av[1][i + 1] >= 33 && av[1][i + 1] <= 126)
// 				j = i + 1;
// 		}
// 		while (av[1][j] >= 33 && av[1][j] <= 127)
// 		{
// 			write(1, &av[1][j++], 1);
// 		}
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }

#include <unistd.h>

int	main(int ac, char *av[])
{
	int	i;
	int	end;

	i = 0;
	if (ac == 2)
	{
		while (av[1][i])
			i++;
		i--;
		if (i >= 0)
		{
			while (i >= 0 && (av[1][i] == 32 || av[1][i] == 9))
				i--;
			end = i;
			while (i >= 0 && av[1][i] != 32 && av[1][i] != 9)
				i--;
			i++;
			while (i <= end)
			{
				write(1, &av[1][i], 1);
				i++;
			}
		}
	}
	write(1, "\n", 1);
}
