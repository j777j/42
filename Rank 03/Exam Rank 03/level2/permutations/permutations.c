/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 16:56:09 by juwang            #+#    #+#             */
/*   Updated: 2025/07/26 16:56:11 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>  // For puts
#include <stdlib.h> // For malloc, free

// Helper function to get string length
static int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

// Helper function to swap two characters
static void	swap(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// Sorts the string to ensure lexicographical output order
static void	sort_string(char *s, int n)
{
	int	i;
	int	j;

	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (s[i] > s[j])
				swap(&s[i], &s[j]);
			j++;
		}
		i++;
	}
}

// The core recursive function to generate and print permutations
void	generate_permutations(char *s, int start, int n)
{
	int	i;

	// Base case: a permutation is found, print it using puts.
	if (start == n - 1)
	{
		puts(s);
		return ;
	}
	i = start;
	while (i < n)
	{
		swap(&s[start], &s[i]);
		// Recurse on the rest of the string
		generate_permutations(s, start + 1, n);
		// Backtrack: swap back to the original state for the next iteration
		swap(&s[start], &s[i]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	char *s_copy;
	int len;

	if (argc != 2)
		return (1);

	len = ft_strlen(argv[1]);
	// Create a modifiable copy of the input string
	s_copy = (char *)malloc(sizeof(char) * (len + 1));
	if (!s_copy)
		return (1);

	int i = -1;
	while (++i < len)
		s_copy[i] = argv[1][i];
	s_copy[i] = '\0';

	// Sort the string first to ensure alphabetical order of permutations
	sort_string(s_copy, len);

	// Start the permutation generation
	generate_permutations(s_copy, 0, len);

	free(s_copy);
	return (0);
}
