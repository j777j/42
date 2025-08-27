/*
Assignment name  : rostring
Expected files   : rostring.c
Allowed functions: write, malloc, free
--------------------------------------------------------------------------------

Write a program that takes a string and displays this string after rotating it
one word to the left.

Thus, the first word becomes the last, and others stay in the same order.

A "word" is defined as a part of a string delimited either by spaces/tabs, or
by the start/end of the string.

Words will be separated by only one space in the output.

If there's less than one argument, the program displays \n.

Example:

$>./rostring "abc   " | cat -e
abc$
$>
$>./rostring "Que la      lumiere soit et la lumiere fut"
la lumiere soit et la lumiere fut Que
$>
$>./rostring "     AkjhZ zLKIJz , 23y"
zLKIJz , 23y AkjhZ
$>
$>./rostring "first" "2" "11000000"
first
$>
$>./rostring | cat -e
$
$>
*/

/////////first one longer
// #include <ctype.h>
// #include <unistd.h>

// // 跳过字符串开头的空白字符
// static char	*skip_spaces(char *str)
// {
// 	while (*str && isspace(*str))
// 	{
// 		str++;
// 	}
// 	return (str);
// }

// // 找到单词的结尾
// static char	*find_word_end(char *str)
// {
// 	while (*str && !isspace(*str))
// 	{
// 		str++;
// 	}
// 	return (str);
// }

// // 旋转字符串
// void	rotate_string(char *str)
// {
// 	char	*first_word_start;
// 	char	*first_word_end;
// 	char	*current_pos;
// 	char	*word_end;

// 	if (!str || !*str)
// 	{
// 		return ;
// 	}
// 	first_word_start = skip_spaces(str);
// 	first_word_end = find_word_end(first_word_start);
// 	current_pos = first_word_end;
// 	// 打印除第一个单词以外的所有单词
// 	while (*current_pos)
// 	{
// 		current_pos = skip_spaces(current_pos);
// 		if (!*current_pos)
// 		{
// 			break ;
// 		}
// 		word_end = find_word_end(current_pos);
// 		write(1, current_pos, word_end - current_pos);
// 		write(1, " ", 1);
// 		current_pos = word_end;
// 	}
// 	// 打印第一个单词
// 	if (first_word_start != first_word_end)
// 	{
// 		write(1, first_word_start, first_word_end - first_word_start);
// 	}
// 	write(1, "\n", 1);
// }

// int	main(int ac, char **av)
// {
// 	if (ac >= 2)
// 	{
// 		rotate_string(av[1]);
// 	}
// 	else
// 	{
// 		write(1, "\n", 1);
// 	}
// 	return (0);
// }

// second one shorter-----------------------------------------

// #include <unistd.h>

// int		skip_whitespace(char *str, int i)
// {
// 	while (str[i] == ' ' || str[i] == '\t')
// 		++i;
// 	return (i);
// }

// int		ft_wordlen(char *str)
// {
// 	int i = 0;

// 	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
// 		++i;
// 	return (i);
// }

// int		print_word(char *str, int i, int *is_first)
// {
// 	int word_len;

// 	i = skip_whitespace(str, i);
// 	word_len = ft_wordlen(str + i);
// 	if (*is_first == 0)
// 		write(1, " ", 1);
// 	write(1, str + i, word_len);
// 	*is_first = 0;
// 	return (i + word_len);
// }

// int		epur_str(char *str)
// {
// 	int i = 0;
// 	int is_first = 1;

// 	i = skip_whitespace(str, i);
// 	while (str[i] != '\0')
// 	{
// 		i = print_word(str, i, &is_first);
// 		i = skip_whitespace(str, i);
// 	}
// 	return (is_first);
// }

// int		main(int argc, char **argv)
// {
// 	if (argc >= 2)
// 	{
// 		char *str = argv[1];
// 		int i = 0;
// 		int is_first;

// 		i = skip_whitespace(str, i);
// 		i = i + ft_wordlen(str + i);
// 		is_first = epur_str(str + i);
// 		print_word(str, 0, &is_first);
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }

// short and ok!!-----------------------------------
// #include <unistd.h>

// int	is_space(char c)
// {
// 	if (c == ' ' || c == '\t')
// 		return (1);
// 	return (0);
// }

// int	main(int argc, char **argv)
// {
// 	int	i;
// 	int	start;
// 	int	end;
// 	int	first;

// 	if (argc >= 2)
// 	{
// 		i = 0;
// 		while (argv[1][i] && is_space(argv[1][i]))
// 			i++;
// 		start = i;
// 		while (argv[1][i] && !is_space(argv[1][i]))
// 			i++;
// 		end = i;
// 		first = 0;
// 		while (argv[1][i])
// 		{
// 			while (argv[1][i] && is_space(argv[1][i]))
// 				i++;
// 			if (first)
// 				write(1, " ", 1);
// 			while (argv[1][i] && !is_space(argv[1][i]))
// 			{
// 				write(1, &argv[1][i], 1);
// 				i++;
// 				first = 1;
// 			}

// 		}
// 		if (first)
// 			write(1, " ", 1);
// 		while (start < end)
// 		{
// 			write(1, &argv[1][start], 1);
// 			start++;
// 		}
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }
//-----------------------------------------------------
// short and with only one function

// from chapi but long but ok for tester
// #include <unistd.h>

// int	skip_whitespace(char *str, int i)
// {
// 	while (str[i] == ' ' || str[i] == '\t')
// 		i++;
// 	return (i);
// }

// int	word_length(char *str, int i)
// {
// 	int	len;

// 	len = 0;
// 	while (str[i + len] != '\0' && str[i + len] != ' ' && str[i+ len] != '\t')
// 		len++;
// 	return (len);
// }

// void	print_word(char *str, int start, int len, int *first)
// {
// 	if (!(*first))
// 		write(1, " ", 1);
// 	write(1, str + start, len);
// 	*first = 0;
// }

// int	main(int argc, char **argv)
// {
// 	char	*str;
// 	int		i;
// 	int		first_word_start;
// 	int		first_word_len;
// 	int		first;
// 	int		len;

// 	if (argc < 2)
// 	{
// 		write(1, "\n", 1);
// 		return (0);
// 	}
// 	str = argv[1];
// 	i = 0;
// 	first_word_start = 0;
// 	first_word_len = 0;
// 	first = 1;
// 	// 找到第一個單字
// 	i = skip_whitespace(str, i);
// 	first_word_start = i;
// 	first_word_len = word_length(str, i);
// 	i += first_word_len;
// 	// 從第一個單字之後開始印出其他單字
// 	while (str[i] != '\0')
// 	{
// 		i = skip_whitespace(str, i);
// 		if (str[i] == '\0')
// 			break ;
// 		len = word_length(str, i);
// 		print_word(str, i, len, &first);
// 		i += len;
// 	}
// 	// 最後印出被移到最後的第一個單字
// 	print_word(str, first_word_start, first_word_len, &first);
// 	write(1, "\n", 1);
// 	return (0);
// }

////////////////////////////
// // another is also good for tester but 5lines more
// #include <stdlib.h>
// #include <unistd.h>

// int	is_space(char c)
// {
// 	if (c == ' ' || c == '\t')
// 		return (1);
// 	return (0);
// }

// void	write_word(char *str, int start, int end)
// {
// 	while (start < end)
// 	{
// 		write(1, &str[start], 1);
// 		start++;
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	char	*str;
// 	int		i;
// 	int		start;
// 	int		end;
// 	int		first_start;
// 	int		first_end;
// 	int		first_word_printed;

// 	if (argc < 2)
// 	{
// 		write(1, "\n", 1);
// 		return (0);
// 	}
// 	str = argv[1];
// 	i = 0;
// 	first_word_printed = 0;
// 	while (str[i] && is_space(str[i]))
// 		i++;
// 	first_start = i;
// 	while (str[i] && !is_space(str[i]))
// 		i++;
// 	first_end = i;
// 	while (str[i])
// 	{
// 		while (str[i] && is_space(str[i]))
// 			i++;
// 		if (str[i] == '\0')
// 			break ;
// 		start = i;
// 		while (str[i] && !is_space(str[i]))
// 			i++;
// 		end = i;
// 		if (first_word_printed)
// 			write(1, " ", 1);
// 		write_word(str, start, end);
// 		first_word_printed = 1;
// 	}
// 	if (first_end > first_start)
// 	{
// 		if (first_word_printed)
// 			write(1, " ", 1);
// 		write_word(str, first_start, first_end);
// 	}
// 	write(1, "\n", 1);
// 	return (0);
// }


//OMG I did it with 38 lines and totally by myself, so short? I can not believe.
#include <unistd.h>

int	main(int ac, char *av[])
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	if (ac >= 2)
	{
		while (av[1][i] && (av[1][i] == ' ' || av[1][i] == '\t'))
			i++;
		while (av[1][i] && (av[1][i] != ' ' && av[1][i] != '\t'))
			i++;
		while (av[1][i])
		{
			while (av[1][i] && (av[1][i] == ' ' || av[1][i] == '\t'))
				i++;
			if (space)
				write(1, " ", 1);
			while (av[1][i] && (av[1][i] != ' ' && av[1][i] != '\t'))
			{
				write(1, &av[1][i++], 1);
				space = 1;
			}
		}
		if (space)
			write(1, " ", 1);
		i = 0;
		while (av[1][i] && (av[1][i] == ' ' || av[1][i] == '\t'))
			i++;
		while (av[1][i] && (av[1][i] != ' ' && av[1][i] != '\t'))
			write(1, &av[1][i++], 1);
	}
	write(1, "\n", 1);
}
