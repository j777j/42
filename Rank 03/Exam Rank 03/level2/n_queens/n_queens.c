/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:53:25 by juwang            #+#    #+#             */
/*   Updated: 2025/07/26 16:53:28 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // for atoi
#include <unistd.h> // for write

// Helper function to write a single character
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

// Helper function to write a number
void	ft_putnbr(int n)
{
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		ft_putchar(n + '0');
	}
}

// Rewritten print function using `write`
void	print_solution(int *board, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		ft_putnbr(board[i]);
		if (i < n - 1)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

// Check if a queen can be placed at board[col] = row
// The logic of this function was already correct.
int	is_safe(int *board, int col, int row)
{
	int	prev_col;

	prev_col = 0;
	while (prev_col < col)
	{
		// Check for same row or diagonal attack
		if (board[prev_col] == row || board[prev_col] - row == col - prev_col
			|| row - board[prev_col] == col - prev_col)
			return (0); // Not safe
		prev_col++;
	}
	return (1); // Safe
}

// The core backtracking solver
void	solve(int *board, int col, int n)
{
	int	row;

	// Base case: If all queens are placed, print the solution
	if (col == n)
	{
		print_solution(board, n);
		return ;
	}
	// Try placing a queen in each row of the current column
	row = 0;
	while (row < n)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			// Recur for the next column
			solve(board, col + 1, n);
		}
		row++;
	}
}

int	main(int argc, char **argv)
{
	int n;
	// Use a static array on the stack instead of malloc
	// This sets a maximum board size, e.g., 12.
	int board[12];

	// Check if exactly one argument is provided
	if (argc != 2)
	{
		return (1);
	}

	n = atoi(argv[1]);

	// Ensure n is within our program's limit and is solvable
	if (n <= 0 || n > 12)
	{
		return (1);
	}

	solve(board, 0, n);
	return (0);
}
