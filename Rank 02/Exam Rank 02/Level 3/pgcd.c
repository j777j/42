/*
Assignment name  : pgcd
Expected files   : pgcd.c
Allowed functions: printf, atoi, malloc, free
--------------------------------------------------------------------------------

Write a program that takes two strings representing two strictly positive
integers that fit in an int.

Display their highest common denominator followed by a newline (It's always a
strictly positive integer).

If the number of parameters is not 2, display a newline.

Examples:

$> ./pgcd 42 10 | cat -e
2$
$> ./pgcd 42 12 | cat -e
6$
$> ./pgcd 14 77 | cat -e
7$
$> ./pgcd 17 3 | cat -e
1$
$> ./pgcd | cat -e
$
*/

#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	int	num1;
	int	num2;

	if (ac == 3)
	{
		// I won't explain the whole thing
		// but if we take 14 and 77 as input we would
		// have the following (each iteration separated by ;)
		// 14; 14; 14; 14; 14; 14; 7
		// 77; 63; 49; 35; 21; 7;  7
		num1 = atoi(av[1]);
		num2 = atoi(av[2]);
		if (num1 > 0 && num2 > 0)
			//因此，您不需要显式地检查 num1 > 0&& num2 > 0。因为根据题目要求，传递给程序的参数已经被保证是严格正数了。
		{
			while (num1 != num2)
			{
				if (num1 > num2)
					num1 = num1 - num2;
				else
					num2 = num2 - num1;
			}
			printf("%d", num1);
		}
	}
	printf("\n");
}
