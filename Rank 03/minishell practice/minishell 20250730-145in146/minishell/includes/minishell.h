/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:00:00 by juwang            #+#    #+#             */
/*   Updated: 2025/07/22 12:00:00 by juwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --- Project Headers --- */
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"

/* --- External Libraries --- */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

/* --- Macros --- */

# define PROMPT "minishell> "
# define O_HEREDOC 0x1000
# define PARENT_PROMPT 0
# define CHILD_EXEC 1

/* --- Data Structures --- */

/**
 * @brief Enum for token types.
 *
 * TOKEN_WORD: A word (e.g., a command, an argument).
 * TOKEN_PIPE: A pipe character '|'.
 * TOKEN_REDIR_IN: An input redirection '<'.
 * TOKEN_REDIR_OUT: An output redirection '>'.
 * TOKEN_REDIR_APPEND: An append output redirection '>>'.
 * TOKEN_HEREDOC: A here-document delimiter '<<'.
 * TOKEN_EOF: End of file/input.
 */
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_SEMICOLON,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}	t_token_type;

/**
 * @brief Structure for a single token.
 *
 * @param type The type of the token from e_token_type.
 * @param value The actual string value of the token.
 * @param next Pointer to the next token in the list.
 */
typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

/* --- Abstract Syntax Tree (AST) Structures --- */

typedef enum e_node_type
{
	NODE_EXEC,
	NODE_PIPE,
	NODE_REDIR,
	NODE_SEQ
}	t_node_type;

typedef struct s_cmd
{
	t_node_type	type;
}	t_cmd;

typedef struct s_exec_cmd
{
	t_node_type	type; // NODE_EXEC
	char		**argv;
}	t_exec_cmd;

typedef struct s_redir_cmd
{
	t_node_type	type; // NODE_REDIR
	t_cmd		*cmd;
	char		*file;
	int			mode; // e.g., O_RDONLY, O_WRONLY | O_CREAT | O_TRUNC, etc.
	int			fd;
}	t_redir_cmd;

typedef struct s_pipe_cmd
{
	t_node_type	type; // NODE_PIPE
	t_cmd		*left;
	t_cmd		*right;
}	t_pipe_cmd;

typedef struct s_seq_cmd
{
	t_node_type type; // NODE_SEQ
	t_cmd		*left;
	t_cmd		*right;
} t_seq_cmd;

/* --- Shell State Structures --- */

/**
 * @brief Structure for a single environment variable.
 *
 * @param key The variable name.
 * @param value The variable value.
 */
typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

/**
 * @brief Main shell structure to hold state.
 *
 * @param env_list The list of environment variables (t_list of t_env).
 * @param exit_status The exit status of the last command.
 */
typedef struct s_shell
{
	t_list	*env_list;
	int		exit_status;
}	t_shell;


/* --- Function Prototypes --- */

/* init.c */
void	init_shell(t_shell *shell, char **envp);
void	free_shell(t_shell *shell);
void	set_env_value(t_shell *shell, char *key, char *value);


/* signals.c */
void	setup_signals(int mode);

/* lexer.c */
t_token	*lexer(const char *line, t_shell *shell);
void	free_tokens(t_token *tokens);
t_token	*new_token(t_token_type type, char *value);
void	add_token_back(t_token **tokens, t_token *new);

/* parser.c */
t_cmd	*parse_command(t_token **tokens, t_shell *shell);
void	free_ast(t_cmd *cmd);

/* parser_utils.c */
t_cmd	*new_exec_cmd(void);
t_cmd	*new_redir_cmd(t_cmd *subcmd, char *file, int mode, int fd);
t_cmd	*new_pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd	*new_seq_cmd(t_cmd *left, t_cmd *right);
void	add_arg_to_exec_cmd(t_exec_cmd *ecmd, char *arg);
t_token_type	peek_type(t_token **tokens);
void	consume_token(t_token **tokens);


/* executor.c */
void	execute_ast(t_cmd *cmd, t_shell *shell);

/* executor_utils.c */
char	*find_command_path(const char *cmd, t_shell *shell);
char	**env_list_to_array(t_list *env_list);
char	*get_env_value(t_list *env_list, const char *key);
t_env	*get_env_by_key(t_list *env_list, const char *key);
int		is_builtin(const char *name);
int		is_parent_builtin(const char *name);
int		dispatch_builtin(t_exec_cmd *cmd, t_shell *shell);


/* builtins */
int		ft_echo(char **args);
int		ft_cd(char **args, t_shell *shell);
int		ft_pwd(void);
int		ft_export(char **args, t_shell *shell);
int		ft_unset(char **args, t_shell *shell);
int		ft_env(t_shell *shell);
void	ft_exit(char **args, t_shell *shell);




#endif
