/*

Assignment name  : union
Expected files   : union.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and displays, without doubles, the
characters that appear in either one of the strings.

The display will be in the order characters appear in the command line, and
will be followed by a \n.

If the number of arguments is not 2, the program displays \n.

Example:

$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>

*/

// #include <unistd.h>

// int	check(int c, char *s, int index)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < index)
// 	{
// 		if (s[i] == c)
// 			return (0);
// 	}
// 	return (1);
// }

// int	main(int ac, char **av)
// {
// 	int	len;
// 	int	j;
// 	int	k;

// 	if (ac == 3)
// 	{
// 		len = -1;
// 		j = 0;
// 		k = 0;
// 		while (av[1][++len])
// 			;
// 		while (av[2][j])
// 		{
// 			av[1][len] = av[2][j];
// 			len++;
// 			j++;
// 		}
// 		av[1][len] = '\0';
// 		len--;
// 		while (k <= len)
// 		{
// 			if (check(av[1][k], av[1], k))
// 				write(1, &av[1][k], 1);
// 			k++;
// 		}
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }

// another

#include <unistd.h>

int	main(int ac, char **av)
{
	int	i;

	char seen[256] = {0}; // 先全部初始化為0
	if (ac == 3)
	{
		i = 0;
		while (av[1][i])
		{
			if (seen[(unsigned char)av[1][i]] == 0)
			{
				seen[(unsigned char)av[1][i]] = 1;
				write(1, &av[1][i], 1);
			}
			i++;
		}
		i = 0;
		while (av[2][i])
		{
			if (seen[(unsigned char)av[2][i]] == 0)
			{
				seen[(unsigned char)av[2][i]] = 1;
				write(1, &av[2][i], 1);
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}

// another
// #include <unistd.h>

// int	main(int ac, char **av)
// {
// 	int	i;
// 	int	lookup[256] = {};

// 	i = 0;
// 	// create a lookup table for all chars in ascii table
// 	if (ac == 3)
// 	{
// 		// loop over the whole first string
// 		// for each character, switch the value in
// 		// the lookup table
// 		while (av[1][i])
// 			lookup[(int)av[1][i++]] = 1;
// 		i = 0;
// 		// do the same thing for the second string
// 		while (av[2][i])
// 			lookup[(int)av[2][i++]] = 1;
// 		i = 0;
// 		// loop over the first string to write the
// 		// seen chars to the screen, switch back the
// 		// value in the lookup table once printed
// 		while (av[1][i])
// 		{
// 			if (lookup[(int)av[1][i]])
// 			{
// 				write(1, &av[1][i], 1);
// 				lookup[(int)av[1][i]] = 0;
// 			}
// 			i++;
// 		}
// 		i = 0;
// 		while (av[2][i])
// 		{
// 			if (lookup[(int)av[2][i]])
// 			{
// 				write(1, &av[2][i], 1);
// 				lookup[(int)av[2][i]] = 0;
// 			}
// 			i++;
// 		}
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }
