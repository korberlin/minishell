/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:01:55 by azsonmez          #+#    #+#             */
/*   Updated: 2024/07/24 13:40:18 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_heredoc;

t_data	*init_data(void)
{
	t_data	*shell;

	shell = (t_data *)malloc(sizeof(t_data));
	if (!shell)
	{
		ft_putstr_fd("Error: Not enough memory to create main data structure\n"\
					, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	shell->err_status = SUCCESS;
	return (shell);
}

void	check_pipe(t_data *shell)
{
	int	len;
	int	i;

	len = ft_strlen(shell->input);
	i = 0;
	while (ft_isspace(shell->input[i]))
		i++;
	if (shell->input[i] == '|')
	{
		ft_err(shell, "pipe");
		shell->err_status = FAIL;
		return ;
	}
	i = len - 1;
	while (i >= 0 && ft_isspace(shell->input[i]))
		i--;
	if (shell->input[i] == '|')
	{
		ft_err(shell, "pipe");
		shell->err_status = FAIL;
		return ;
	}
	return ;
}

void	minishell_loop(t_data *shell)
{
	while (1)
	{
		reset_shell(shell);
		handle_signals(shell);
		shell->input = readline(GREEN "💀 minishell> " RESET);
		if (!shell->input)
		{
			write(1, "exit\n", 5);
			ft_err(shell, "none");
			return ;
		}
		add_history(shell->input);
		handle_signals(shell);
		check_pipe(shell);
		if (shell->err_status == 0)
			lexer(shell);
		if (shell->err_status == 0)
			parser(shell);
		if (shell->err_status == 0)
			executor(shell);
		free_shell(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*shell;

	(void)argv;
	(void)argc;
	shell = init_data();
	shell->exit = 0;
	shell->envp = envp;
	shell->env = create_env(envp);
	print_welcome();
	minishell_loop(shell);
}
