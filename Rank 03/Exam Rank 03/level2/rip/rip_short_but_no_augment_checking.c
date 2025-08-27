// Assignment name: rip
// Expected files: *.c *.h
// Allowed functions: puts, write
// --------------------------------------------------------------------------------
// Write a program that will take as argument a string containing only parenthesis.
// If parenthesis are unbalanced (for example "())") your program shall remove the
// minimum number of parenthesis for the expression to be balanced.
// By removing we mean replacing by spaces.
// You will print all the solutions (can be more than one).
// The order of the solutions is not important.
// For example this should work:
// (For readability reasons the '_' means space and the spaces are for readability only.)
// $> ./rip '( ( )' | cat -e
// _ ( ) $
// ( _ ) $
// $> ./rip '( ( ( ) ( ) ( ) ) ( ) )' | cat -e
// ( ( ( ) ( ) ( ) ) ( ) ) $
// $> ./rip '( ) ( ) ) ( )' | cat -e
// ( ) ( ) _ ( ) $
// ( ) ( _ ) ( ) $
// ( _ ( ) ) ( ) $
// $> ./rip '( ( ) ( ( ) (' | cat -e
// ( ( ) _ _ ) _ $
// ( _ ) ( _ ) _ $
// ( _ ) _ ( ) _ $
// _ ( ) ( _ ) _ $
// _ ( ) _ ( ) _ $

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int		invalid(char *s);

int	invalid(char *s)
{
	int	opened;
	int	closed;

	opened = 0;
	closed = 0;
	for (int x = 0; s[x]; x++)
	{
		if (s[x] == '(')
			opened++;
		else if (s[x] == ')')
		{
			if (opened > 0)
				opened--;
			else
				closed++;
		}
	}
	return (closed + opened);
}

void	solve(char *s, int must_fix, int fixed, int pos)
{
	char	c;

	if (must_fix == fixed && !invalid(s))
	{
		puts(s);
		return ;
	}
	for (int x = pos; s[x]; x++)
	{
		if (s[x] == '(' || s[x] == ')')
		{
			c = s[x];
			s[x] = ' ';
			solve(s, must_fix, fixed + 1, x + 1);
			s[x] = c;
		}
	}
}

int	main(int ac, char **av)
{
	int	must_fix;

	(void)ac; // needs to be changed
	must_fix = invalid(av[1]);
	solve(av[1], must_fix, 0, 0);
}
