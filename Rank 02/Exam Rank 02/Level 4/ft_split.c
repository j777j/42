#include <stdlib.h>

char	**ft_split(char *str)
{
	int		i;
	int		j;
	int		k;
	char	**split;

	i = 0;
	k = 0;
	if (!(split = (char **)malloc(sizeof(char *) * 256)))
		return (NULL);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[i])
	{
		j = 0;
		if (!(split[k] = (char *)malloc(sizeof(char) * 4096)))
			return (NULL);
		while (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i])
			split[k][j++] = str[i++];
		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			i++;
		split[k][j] = '\0';
		k++;
	}
	split[k] = NULL;
	return (split);
}

/// wuwuwuwuwu this is the first time i wrote my own split immedately right and i write this test! i knew nothing about string! also the Gemini gave me such a long one !

// int	main(void)
// {
// 	char	**str;
// 	char	*s;
// 	int		i;

// 	i = 0;
// 	s = " lig  wdk    723g";
// 	str = ft_split(s);
// 	while (str[i])
// 	{
// 		printf("%s", str[i]);
// 		printf("\n");
// 		i++;
// 	}
// }

// This one is also ok for tester,it is so much longer but safer because the malloc is always exactly
// #include "stdlib.h"
// #include "unistd.h"

// int	count_words(char *str)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (str[i] != '\0')
// 	{
// 		while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
// 			i++;
// 		if (str[i] != '\0')
// 			count++;
// 		while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t'
// 			&& str[i] != '\n')
// 			i++;
// 	}
// 	return (count);
// }

// void	copy_words(char *tab, char *str, int start, int end)
// {
// 	int	j;

// 	j = 0;
// 	while (start < end)
// 		tab[j++] = str[start++];
// 	tab[j] = '\0';
// }

// int	find_next_word(char *str, int *start, int *end)
// {
// 	int	i;

// 	i = *end;
// 	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'
// 			|| str[i] == '\n'))
// 		i++;
// 	*start = i;
// 	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
// 		i++;
// 	*end = i;
// 	return (*start < *end);
// }

// int	ft_fill_words(char **tab, char *str)
// {
// 	int	i;
// 	int	word;
// 	int	start;
// 	int	end;

// 	i = 0;
// 	word = 0;
// 	start = 0;
// 	end = 0;
// 	while (find_next_word(str, &start, &end))
// 	{
// 		tab[word] = malloc((end - start + 1) * sizeof(char));
// 		if (tab[word] == NULL)
// 		{
// 			i = 0;
// 			while (i < word)
// 				free(tab[i++]);
// 			free(tab);
// 			return (0);
// 		}
// 		copy_words(tab[word], str, start, end);
// 		word++;
// 	}
// 	tab[word] = NULL;
// 	return (1);
// }

// char	**ft_split(char *str)
// {
// 	char	**out;
// 	int		size;

// 	size = count_words(str);
// 	out = malloc((sizeof(char *) * (size + 1)));
// 	if (!out)
// 		return (NULL);
// 	if (!ft_fill_words(out, str))
// 	{
// 		free(out);
// 		return (NULL);
// 	}
// 	return (out);
// }

// This one below is also ok for test and just checking which one is easier for me to remember. Also I have my own one in libft.
// #include <stdio.h>
// #include <stdlib.h>

// int	check_separator(char c)
// {
// 	if (c == 9 || c == 32 || c == 10)
// 		return (1);
// 	return (0);
// }

// static int	count_strings(char const *str)
// {
// 	int	i;
// 	int	count;

// 	count = 0;
// 	i = 0;
// 	while (str[i])
// 	{
// 		while (str[i] && check_separator(str[i]))
// 			i++;
// 		if (str[i])
// 			count++;
// 		while (str[i] && !check_separator(str[i]))
// 			i++;
// 	}
// 	return (count);
// }

// static char	*ft_word(const char **str)
// {
// 	int			len_word;
// 	int			i;
// 	const char	*start;
// 	char		*word;

// 	len_word = 0;
// 	start = *str;
// 	while (**str && !check_separator(**str))
// 	{
// 		len_word++;
// 		(*str)++;
// 	}
// 	word = (char *)malloc(sizeof(char) * (len_word + 1));
// 	if (!word)
// 		return (NULL);
// 	*str = start;
// 	i = 0;
// 	while (i < len_word)
// 	{
// 		word[i] = **str;
// 		(*str)++;
// 		i++;
// 	}
// 	word[len_word] = '\0';
// 	return (word);
// }

// static void	*ft_free_all_split_alloc(char **split, size_t elts)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < elts)
// 	{
// 		free(split[i]);
// 		i++;
// 	}
// 	free(split);
// 	return (NULL);
// }

// char	**ft_split(char const *str)
// {
// 	int		i;
// 	char	**strings;

// 	if (!str)
// 		return (NULL);
// 	strings = (char **)malloc(sizeof(char *) * (count_strings(str) + 1));
// 	if (!strings)
// 		return (NULL);
// 	i = 0;
// 	while (*str)
// 	{
// 		while (*str && check_separator(*str))
// 			str++;
// 		if (*str)
// 		{
// 			strings[i] = ft_word(&str);
// 			if (!strings[i])
// 				return (ft_free_all_split_alloc(strings, i));
// 			i++;
// 		}
// 	}
// 	strings[i] = 0;
// 	return (strings);
// }
