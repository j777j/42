/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/08/06 13:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"

/*
** State tracking for the expansion process of a single word.
** result_list: A pointer to the list where final words are stored.
** current_word: The word currently being built.
** in_quotes: Flag for single quote state.
** in_dquotes: Flag for double quote state.
*/
typedef struct s_expand_state
{
	t_list	**result_list;
	char	*current_word;
	int		in_quotes;
	int		in_dquotes;
}	t_expand_state;

/* --- Main Expander --- */
void	expand_ast(t_cmd *cmd, t_shell *shell);

/* --- Core Expansion Logic --- */
void	expand_and_split_word(char *word, t_shell *shell, t_list **list);

/* --- Utils --- */
void	append_char_to_word(char **word, char c);
char	**ft_lst_to_array(t_list *lst);

#endif
