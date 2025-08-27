/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/01 14:20:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

typedef struct s_expand_state
{
	const char	*arg;
	char		*result;
	char		quote_state;
}	t_expand_state;

// --- Main Expander ---
void	expand_command_args(t_exec_cmd *cmd, t_shell *shell);

// --- Stage 1: Expansion ---
char	*perform_parameter_expansion(const char *arg, t_shell *shell);

// --- Stage 2: Word Splitting ---
t_list	*perform_word_splitting(char *expanded_str, const char *original_arg);

// --- Stage 3: Quote Removal ---
char	*perform_quote_removal(char *arg);

// --- Utils ---
char	*get_env_value(t_list *env_list, const char *name);
char	**ft_lst_to_array(t_list *lst);
void	append_char(char **s, char c);
void	append_str(char **s1, char *s2);

#endif
