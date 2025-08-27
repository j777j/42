/*

Assignment name  : add_prime_sum
Expected files   : add_prime_sum.c
Allowed functions: write, exit
--------------------------------------------------------------------------------

Write a program that takes a positive integer as argument and displays the sum
of all prime numbers inferior or equal to it followed by a newline.

If the number of arguments is not 1, or the argument is not a positive number,
just display 0 followed by a newline.

Yes, the examples are right.

Examples:

$>./add_prime_sum 5
10
$>./add_prime_sum 7 | cat -e
17$
$>./add_prime_sum | cat -e
0$
$>

*/

// #include <unistd.h> // For write

// void	ft_small_putnbr(int nbr)
// {
// 	char	digit_char;

// 	if (nbr > 9)
// 	{
// 		ft_small_putnbr(nbr / 10);
// 		ft_small_putnbr(nbr % 10);
// 	}
// 	else
// 	{
// 		digit_char = nbr + '0';
// 		write(1, &digit_char, 1);
// 	}
// }

// int	ft_is_prime(int nbr)
// {
// 	int	check;

// 	check = 2;
// 	if (nbr <= 1)
// 		return (0);
// 	while (check < nbr)
// 	{
// 		if ((nbr % check) == 0)
// 			return (0);
// 		check++;
// 	}
// 	return (1);
// }

// int	ft_short_atoi(char *str)
// {
// 	int	idx;
// 	int	result;

// 	idx = 0;
// 	result = 0;
// 	while (str[idx] != '\0')
// 	{
// 		result *= 10;
// 		result += str[idx] - '0';
// 		idx++;
// 	}
// 	return (result);
// }

// int	ft_add_prime_sum(int nbr)
// {
// 	int	idx;
// 	int	sum;

// 	idx = 2;
// 	sum = 0;
// 	if (nbr <= 0)
// 		return (0);
// 	while (idx <= nbr)
// 	{
// 		if (ft_is_prime(idx))
// 			sum += idx;
// 		idx++;
// 	}
// 	return (sum);
// }

// int	main(int argc, char **argv)
// {
// 	if (argc == 2)
// 		ft_small_putnbr(ft_add_prime_sum(ft_short_atoi((argv[1]))));
// 	else
// 		write(1, "0", 1);
// 	write(1, "\n", 1);
// 	return (0);
// }

// another!
#include <stdlib.h>
#include <unistd.h>

int	if_prime(int num)
{
	int	i;

	i = 3;
	if (num == 2)
		return (1);
	if (num <= 1 || (num > 2 && num % 2 == 0))
		return (0);
	while (i * i <= num)
	{
		if (num % i == 0)
			return (0);
		i += 2;
	}
	return (1);
}

void	ft_putnbr(int num)
{
	if (num >= 10)
		ft_putnbr(num / 10);
	write(1, &"0123456789"[num % 10], 1);
}

int	ft_atoi(char *s)
{
	int	i;
	int	result;

	// int	sign;
	i = 0;
	// sign = 1;
	result = 0;

	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + s[i] - 48;
		i++;
	}
	// return (result * sign);
	return (result);
}

int	main(int ac, char *av[])
{
	int	j;
	int	sum;

	j = 1;
	sum = 0;
	if (ac == 2)
	{
		while (j <= (ft_atoi(av[1])))
		{
			if (if_prime(j))
				sum += j;
			j++;
		}
	}
	ft_putnbr(sum);
	write(1, "\n", 1);
}
