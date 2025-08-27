#include <unistd.h>

// Helper to print a string followed by a newline.
static void	ft_puts(const char *s)
{
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
}

// Pre-calculates the number of '(' and ')' that must be removed.
static void	calculate_removals(char *s, int *left_rem, int *right_rem)
{
	int	open;
	int	i;

	*left_rem = 0;
	*right_rem = 0;
	open = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '(')
			open++;
		else if (s[i] == ')')
		{
			if (open > 0)
				open--;
			else
				(*right_rem)++;
		}
		i++;
	}
	*left_rem = open;
}

// Optimized recursive solver with pruning.
// s: the string being modified
// index: current position in the string
// l_rem, r_rem: number of left/right parentheses we still need to remove
// open_count: current balance of open parentheses in the path being built
static void	solve_optimized(char *s, int index, int l_rem, int r_rem,
		int open_count)
{
	char	c;

	// Base case: we've processed the whole string.
	if (s[index] == '\0')
	{
		// If all removals are done and the string is balanced, it's a solution.
		if (l_rem == 0 && r_rem == 0 && open_count == 0)
			ft_puts(s);
		return ;
	}
	c = s[index];
	if (c == '(' && l_rem > 0)
	{
		// Choice 1: Remove this '('.
		s[index] = ' ';
		solve_optimized(s, index + 1, l_rem - 1, r_rem, open_count);
		s[index] = c; // Backtrack
	}
	else if (c == ')' && r_rem > 0)
	{
		// Choice 2: Remove this ')'.
		s[index] = ' ';
		solve_optimized(s, index + 1, l_rem, r_rem - 1, open_count);
		s[index] = c; // Backtrack
	}
	// Choice 3: Keep the current character.
	if (c == '(')
		solve_optimized(s, index + 1, l_rem, r_rem, open_count + 1);
	else if (c == ')')
	{
		// Pruning: only keep ')' if it can match an open '('.
		if (open_count > 0)
			solve_optimized(s, index + 1, l_rem, r_rem, open_count - 1);
	}
	else // It's already a space
	{
		solve_optimized(s, index + 1, l_rem, r_rem, open_count);
	}
}

int	main(int argc, char **argv)
{
	int	left_to_remove;
	int	right_to_remove;

	if (argc != 2)
		return (1);
	calculate_removals(argv[1], &left_to_remove, &right_to_remove);
	solve_optimized(argv[1], 0, left_to_remove, right_to_remove, 0);
	return (0);
}
