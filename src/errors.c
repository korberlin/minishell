/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:30:49 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/25 16:08:03 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *error)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	if (ft_strcmp(error, "pipe") == 0)
		ft_putstr_fd("unexpected '|'\n", STDERR_FILENO);
	if (ft_strcmp(error, "quote") == 0)
		ft_putstr_fd("Please close all the quotes\n", STDERR_FILENO);
	if (ft_strcmp(error, "memory") == 0)
		ft_putstr_fd("Couldn't allocate memory\n", STDERR_FILENO);
	if (ft_strcmp(error, "command") == 0)
		ft_putstr_fd("command not found\n", STDERR_FILENO);
	if (ft_strcmp(error, "delimiter") == 0)
		ft_putstr_fd("No heredoc delimiter found\n", STDERR_FILENO);
	if (ft_strcmp(error, "file") == 0)
		ft_putstr_fd("No heredoc delimiter found\n", STDERR_FILENO);
	if (ft_strcmp(error, "pipe(error)") == 0)
		ft_putstr_fd("pipe error\n", STDERR_FILENO);
	if (ft_strcmp(error, "execve") == 0)
		ft_putstr_fd("execve error\n", STDERR_FILENO);
	if (ft_strcmp(error, "directory") == 0)
		ft_putstr_fd("file or directory not found\n", STDERR_FILENO);
	if (ft_strcmp(error, "export") == 0)
		ft_putstr_fd("invalid variable name\n", STDERR_FILENO);
	if (ft_strcmp(error, "toomany") == 0)
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	if (ft_strcmp(error, "numeric") == 0)
		ft_putstr_fd("numeric argument required\n", STDERR_FILENO);
}

void	ft_err(t_data *shell, char *error)
{
	shell->err_status = FAIL;
	if (!(ft_strcmp(error, "none") == 0))
		print_error(error);
	exit_status(shell, error);
}

void	exit_status(t_data *shell, char *error)
{
	if (ft_strcmp(error, "pipe") == 0)
		shell->exit = 1;
	if (ft_strcmp(error, "quote") == 0)
		shell->exit = 1;
	if (ft_strcmp(error, "memory") == 0)
		shell->exit = 1;
	if (ft_strcmp(error, "command") == 0)
		shell->exit = 127;
	if (ft_strcmp(error, "delimiter") == 0)
		shell->exit = 1;
	if (ft_strcmp(error, "file") == 0)
		shell->exit = 1;
	if (ft_strcmp(error, "pipe(error)") == 0)
		shell->exit = 1;
	if (ft_strcmp(error, "execve") == 0)
		shell->exit = 1;
	if (ft_strcmp(error, "directory") == 0)
		shell->exit = 1;
	if (ft_strcmp(error, "export") == 0)
		shell->exit = 1;
	if (ft_strcmp(error, "numeric") == 0)
		shell->exit = 2;
	if (ft_strcmp(error, "toomany") == 0)
		shell->exit = 1;
}

void	ft_exit(t_data *shell, char *error)
{
	int	i;

	ft_err(shell, error);
	free_env(shell->env);
	i = shell->exit;
	free_shell(shell);
	free(shell);
	exit(i);
}

void	free_pipes(t_data *shell, int **pipes)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
		free(pipes[i++]);
	if (pipes)
		free(pipes);
}
