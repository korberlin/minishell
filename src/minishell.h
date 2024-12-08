/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:58:50 by azsonmez          #+#    #+#             */
/*   Updated: 2024/07/25 16:07:03 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <bits/sigaction.h>
# include <bits/types/siginfo_t.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAIL 1
# define YES 1
# define NO 0

extern int	g_heredoc;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_tokens
{
	char				*token;
	struct s_tokens		*next;
}	t_token;

typedef struct s_heredoc
{
	char				*delimiters;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_data
{
	t_env		*env;
	t_token		*tokens;
	t_heredoc	*delimiters;
	char		**envp;
	int			exit;
	int			cmd_count;
	int			truncate;
	int			heredoc_mode;
	int			interactive;
	int			pipe_count;
	int			err_status;
	int			fd_inf;
	int			fd_out;
	int			**pipes;
	pid_t		*children;
	char		***cmds;
	char		**executable_paths;
	char		**paths;
	char		*input;
	char		*std_input;
	char		*std_output;
	char		*heredoc_file;
}	t_data;

// Env
t_env			*add_env(char *env, char *separator);
void			append_env(t_data *shell, char *variable);
t_env			*create_env(char **env);
char			*get_env(t_data *shell, char *var_name);

// Error
void			print_error(char *error);
void			ft_err(t_data *shell, char *error);
void			ft_exit(t_data *shell, char *error);
void			exit_status(t_data *shell, char *error);
void			check_exit_args(t_data *shell);
void			handle_exit_code(t_data *shell, char *arg);

// Free
void			free_2d(char **str);
void			free_3d(char ***cmd);
void			free_env(t_env *env);
void			free_pipes(t_data *shell, int **pipes);
void			free_tokens(t_token **tokens, void (*del)(void*));
void			free_delimiters(t_data *shell);
void			free_shell(t_data *shell);
void			free_shell_2(t_data *shell);

// Init functions
t_data			*init_data(void);
bool			check_path_exists(t_data *shell);
char			**add_slash(char **temp);
void			fill_paths(t_data *shell);
void			reset_shell(t_data *shell);
void			reset_pipes(t_data *shell);

// Signals
void			interactive_signals(void);
void			non_interactive_signals(void);
void			handle_signals(t_data *shell);

// Main
void			check_pipe(t_data *shell);
void			minishell_loop(t_data *shell);

// Lexer
char			*get_remaining_word(char *str);
int				check_quote(bool *sq, bool *dq, char c);
void			tokenizer(t_data *shell, char *str, int *len, int *i);
void			lexer(t_data *shell);
int				is_operator(int c);
int				is_multi_char_operator(const char *str);
void			append_operators(t_data *shell, int *i, int *len, char *str);
t_token			*retrieve_last(t_data *shell);
void			append_token(t_data *shell, char *token);

// Heredoc
int				open_heredoc(t_data *shell);
void			handle_heredoc(t_data *shell);
void			handle_heredoc_2(t_data *shell, char *line);
int				is_delimiter(t_data *shell, char *str);
void			heredoc_delimiter(t_token *iterator, t_data *shell);
t_heredoc		*heredoc_new(t_token *iterator);
void			heredoc_add_back(t_heredoc **lst, t_heredoc *new);

// Parse
void			adjust_command_count(t_token *iterator, t_data *shell);
void			handle_operator(t_data *shell, t_token **iterator);
void			store_commands(t_data *shell, t_token *iterator);
char			**parse_commands(t_data *shell, const char *token);
void			parser(t_data *shell);
void			handle_output_redirection(t_data *shell, t_token **iterator);
int				ft_tokensize(t_token *token);
unsigned int	count_wc(char const *token);
unsigned int	quote_length(char const *token);
char			*find_next(const char *str);

// Expander
char			*variable_value(t_data *shell, char *start, int length);
char			*replace_next_variable(char *result, char *value, \
	char *var_end, char *var_start);
char			*add_variables(t_data *shell, char **str);
void			expander(t_data *shell);
void			eliminate_quotes(char *str, char **output);

// Redirect
void			get_fd(t_data *shell, int i, int fd[2]);
void			restore(t_data *shell, int i, int fd[2], int temp[2]);
void			wait_children(t_data *shell);
void			fork_child(t_data *shell, int i);
void			handle_redirs_2(t_data *shell);

// Execute
int				check_access(t_data *shell, char **command);
int				check_cwd_access(t_data *shell, char **command);
int				loop_command_paths(t_data *shell, char **command, int *tracker);
void			check_commands(t_data *shell);
void			executor(t_data *shell);
int				exec_builtin(t_data *shell, int i);
int				is_builtin(char *command);
void			start_builtin(t_data *shell, char **cmds);
void			handle_redirs(t_data *shell);
void			add_executable_paths(t_data *shell, char *full_name);
void			handle_child_processes(t_data *shell);
int				check_permission(pid_t *children, char *cmd, int i);
int				backup(t_data *shell, int i, int fd[2], int temp[2]);

// Builtins
void			ft_echo(char **cmds);
void			ft_quit(t_data *shell);
void			ft_env(t_data *shell);
void			ft_pwd(t_data *shell, char **cmds);
int				is_name_valid(char *cmd);
void			ft_export(t_data *shell, char **cmds);
void			print_export(t_data *shell);
void			ft_unset(t_data *shell, char **cmds, int j);
void			ft_cd(t_data *shell, char **cmds);
char			*old_pwd(t_data *shell);
void			unset_2(t_data *shell, char *cmds, t_env *iterator);

#endif
