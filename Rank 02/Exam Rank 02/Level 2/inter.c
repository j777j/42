#include <unistd.h>

int	ft_putchar(char c);

int	main(int ac, char **av)
{
	int	i;
	int	j;
	int	lookup[256] = {};

	i = 0;
	// create an array of int that will act as a lookup table
	// 256 is because of the ascii table, each one will
	// correspond to a single character
	if (ac == 3)
	{
		// looping over the whole string
		while (av[1][i])
		{
			j = 0;
			// comparing against every character in the
			// second string
			while (av[2][j])
			{
				// checking if characters are the same
				// as well as checking in the lookup
				// table if the character not already
				// found
				if (av[1][i] == av[2][j] && !lookup[(int)av[2][j]])
				{
					// marking the character found
					// in the lookup table
					lookup[(int)av[2][j]] = 1;
					// writing the character
					// to the screen
					ft_putchar(av[2][j]);
				}
				j++;
			}
			i++;
		}
	}
	ft_putchar('\n');
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}
