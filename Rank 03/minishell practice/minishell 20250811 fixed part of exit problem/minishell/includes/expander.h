/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/30 22:10:00 by juwang           ###   ########.fr       */
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

// Expander
void	expand_command_args(t_exec_cmd *cmd, t_shell *shell);

// Expander Utils
char	*perform_expansion(const char *arg, t_shell *shell);
char	*get_env_value(t_list *env_list, const char *name);


// Expander Split
char	**ft_lst_to_array(t_list *lst);
void	append_str(char **s1, char *s2);

#endif
