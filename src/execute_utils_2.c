/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:04:40 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/25 14:10:54 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	backup(t_data *shell, int i, int fd[2], int temp[2])
{
	temp[0] = dup(STDIN_FILENO);
	temp[1] = dup(STDOUT_FILENO);
	if (temp[0] == -1 || temp[1] == -1)
	{
		shell->err_status = FAIL;
		return (FAIL);
	}
	get_fd(shell, i, fd);
	if (fd[0] != STDIN_FILENO && dup2(fd[0], STDIN_FILENO) == -1)
		ft_err(shell, "pipe(error)");
	if (fd[1] != STDOUT_FILENO && dup2(fd[1], STDOUT_FILENO) == -1)
		ft_err(shell, "pipe(error)");
	return (YES);
}

void	add_executable_paths(t_data *shell, char *full_name)
{
	int	i;

	i = 0;
	if (!shell->executable_paths)
	{
		shell->executable_paths = \
			malloc(sizeof(char **) * (shell->cmd_count + 1));
		if (!shell->executable_paths)
			return (ft_err(shell, "memory"));
		while (i < shell->cmd_count + 1)
			shell->executable_paths[i++] = NULL;
	}
	i = 0;
	while (shell->executable_paths[i])
		i++;
	shell->executable_paths[i] = ft_strdup(full_name);
}

void	handle_redirs(t_data *shell)
{
	if (shell->heredoc_mode)
		shell->fd_inf = open(shell->heredoc_file, O_RDONLY);
	else if (shell->std_input)
		shell->fd_inf = open(shell->std_input, O_RDONLY);
	else
		shell->fd_inf = STDIN_FILENO;
	if (shell->fd_inf < 0)
	{
		shell->err_status = FAIL;
		perror("Error");
		shell->fd_inf = STDIN_FILENO;
	}
	handle_redirs_2(shell);
}

void	handle_redirs_2(t_data *shell)
{
	if (shell->std_output && shell->truncate)
		shell->fd_out = open(shell->std_output, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (shell->std_output)
		shell->fd_out = open(shell->std_output, \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		shell->fd_out = STDOUT_FILENO;
	if (shell->fd_out < 0)
	{
		shell->err_status = FAIL;
		perror("Error");
		shell->fd_out = STDOUT_FILENO;
	}
}
