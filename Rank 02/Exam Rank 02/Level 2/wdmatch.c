/*

Assignment name  : wdmatch
Expected files   : wdmatch.c
Allowed functions: write
--------------------------------------------------------------------------------

Write a program that takes two strings and checks whether it's possible to
write the first string with characters from the second string, while respecting
the order in which these characters appear in the second string.

If it's possible, the program displays the string, followed by a \n, otherwise
it simply displays a \n.

If the number of arguments is not 2, the program displays a \n.

Examples:

$>./wdmatch "faya" "fgvvfdxcacpolhyghbreda" | cat -e
faya$
$>./wdmatch "faya" "fgvvfdxcacpolhyghbred" | cat -e
$
$>./wdmatch "forty two" "qfqfsoudf arzgrsayns tsryegftdgs sjytwdekuooixq " | cat
	-e
forty two$
$>./wdmatch "error" rrerrrfiiljdfxjyuifrrvcoojh | cat -e
$
$>./wdmatch | cat -e
$

*/

// #include <unistd.h>

// void	ft_putstr(char *s)
// {
// 	int	i;

// 	i = -1;
// 	while (s[++i])
// 		write(1, &s[i], 1);
// }

// int	main(int ac, char **av)
// {
// 	int	i;
// 	int	j;

// 	if (ac == 3)
// 	{
// 		if (!av[1][0])
// 		{
// 			ft_putstr(av[1]);
// 			write(1, "\n", 1);
// 			return (0);
// 		}
// 		i = -1;
// 		j = 0;
// 		while (av[2][j])
// 			if (av[2][j++] == av[1][++i])
// 				if (!av[1][i])
// 					ft_putstr(av[1]);
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }

// // another one!!
// #include <unistd.h>

// int	main(int ac, char **av)
// {
// 	const char	*s1 = av[1];
// 	const char	*s2 = av[2];
// 	int			len;
// 	int			i;

// 	if (ac == 3)
// 	{
// 		len = 0;
// 		i = 0;
// 		while (s1[len])
// 			len++;
// 		// checking all characters of s1 in s2
// 		while (i < len && *s2)
// 		{
// 			// next line checks if current s1 char is
// 			// equal to s2 char, after the comparison is
// 			// done, we increment the s2 pointer
// 			// even if the condition doesn't match
// 			// if the condition match, we increment i to
// 			// check for next s1 char
// 			if (s1[i] == *s2++)
// 				i++;
// 		}
// 		if (i == len)
// 			write(1, s1, len);
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }

// // another one!!
// int	search(char a, char *s)
// {
// 	int	k;

// 	k = 0;
// 	while (s[k])
// 	{
// 		if (a == s[k])
// 			return (1);
// 		else
// 			k++;
// 	}
// 	return (0);
// }

// int	len(char *ss)
// {
// 	int	m;

// 	m = 0;
// 	while (*ss)
// 		m++;
// 	return (m);
// }

// void	ft_putstr(char *sss)
// {
// 	while (*sss)
// 		write(1, sss++, 1);
// }

// int	main(int ac, char *av[])
// {
// 	int	i;

// 	if (ac == 3)
// 	{
// 		i = 0;
// 		while (av[1][i])
// 		{
// 			if (search(av[1][i], av[2]))
// 				i++;
// 			else
// 				break ;
// 		}
// 		if (i == len(av[1]))
// 			ft_putstr(av[1]);
// 	}
// 	write(1, "\n", 1);
// }

// best one?

#include <unistd.h>

int	main(int ac, char **av)
{
	int	i;
	int	j;

	if (ac == 3)
	{
		j = 0;
		i = 0;
		while (av[2][j])
		{
			if (av[1][i] == av[2][j])
				i++;
			j++;
		}
		if (!av[1][i])
		{
			i = 0;
			while (av[1][i])
				write(1, &av[1][i++], 1);
		}
	}
	write(1, "\n", 1);
	return (0);
}

// mine! It is mine!
// #include <unistd.h>

// void	ft_putstr(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		write(1, &s[i], 1);
// 		i++;
// 	}
// }

// int	main(int ac, char *av[])
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	j = 0;
// 	if (ac == 3)
// 	{
// 		while (av[1][i] && av[2][j])
// 		{
// 			if (av[1][i] == av[2][j])
// 			{
// 				j++;
// 				i++;
// 			}
// 			else
// 				j++;
// 		}
// 		if (av[1][i] == '\0')
// 			ft_putstr(av[1]);
// 	}
// 	write(1, "\n", 1);
// }
