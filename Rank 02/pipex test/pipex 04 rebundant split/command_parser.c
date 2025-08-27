/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang < juwang@student.42tokyo.jp>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:03:25 by juwang            #+#    #+#             */
/*   Updated: 2025/07/09 15:26:50 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	count_splits_cmd(const char *s)
{
	size_t	count;
	int		in_substring;

	count = 0;
	in_substring = 0;
	while (*s)
	{
		if (*s == ' ')
			in_substring = 0;
		else if (in_substring == 0)
		{
			in_substring = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static size_t	get_substring_len_cmd(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != ' ')
		len++;
	return (len);
}

static int	alloc_copy_single_arg(char **cmd_args, const char *current_pos,
		size_t i, t_pipex *data)
{
	size_t	len;

	len = get_substring_len_cmd(current_pos);
	cmd_args[i] = (char *)malloc(sizeof(char) * (len + 1));
	if (!cmd_args[i])
	{
		free_command_args(cmd_args);
		handle_system_error("Memory alloc failed for cmd arg", data);
		return (0);
	}
	ft_memcpy(cmd_args[i], current_pos, len);
	cmd_args[i][len] = '\0';
	return (1);
}

static char	**handle_initial_cmd_alloc(const char *cmd_str, size_t *num_args,
		t_pipex *data)
{
	char	**cmd_args;

	if (!cmd_str)
		return (NULL);
	*num_args = count_splits_cmd(cmd_str);
	cmd_args = (char **)malloc(sizeof(char *) * (*num_args + 1));
	if (!cmd_args)
	{
		handle_system_error("Failed to allocate memory for command arguments",
			data);
		return (NULL);
	}
	return (cmd_args);
}

char	**parse_command_string(const char *cmd_str, t_pipex *data)
{
	char		**cmd_args;
	size_t		num_args;
	size_t		i;
	const char	*temp_str_ptr;

	cmd_args = handle_initial_cmd_alloc(cmd_str, &num_args, data);
	if (!cmd_args)
		return (NULL);
	i = 0;
	temp_str_ptr = cmd_str;
	while (i < num_args)
	{
		while (*temp_str_ptr == ' ' && *temp_str_ptr != '\0')
			temp_str_ptr++;
		if (!alloc_copy_single_arg(cmd_args, temp_str_ptr, i, data))
			return (NULL);
		temp_str_ptr += get_substring_len_cmd(temp_str_ptr);
		i++;
	}
	cmd_args[num_args] = NULL;
	return (cmd_args);
}
