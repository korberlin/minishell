/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:45:21 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/25 13:37:20 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_fd(t_data *shell, int i, int fd[2])
{
	if (i == 0)
		fd[0] = shell->fd_inf;
	else
		fd[0] = shell->pipes[i - 1][0];
	if (i == shell->cmd_count - 1)
		fd[1] = shell->fd_out;
	else
		fd[1] = shell->pipes[i][1];
}

void	restore(t_data *shell, int i, int fd[2], int temp[2])
{
	if (i > 0)
		close(shell->pipes[i - 1][0]);
	if (i < shell->cmd_count - 1)
		close(shell->pipes[i][1]);
	if (fd[0] != STDIN_FILENO && dup2(temp[0], STDIN_FILENO) == -1)
		ft_exit(shell, "pipe(error)");
	if (fd[1] != STDOUT_FILENO && dup2(temp[1], STDOUT_FILENO) == -1)
		ft_exit(shell, "pipe(error)");
	if (fd[0] > 2)
		close(fd[0]);
	if (fd[1] > 2)
		close(fd[1]);
	close(temp[0]);
	close(temp[1]);
}

void	wait_children(t_data *shell)
{
	int	i;
	int	child_process;

	child_process = 0;
	i = 0;
	while (i < shell->cmd_count)
	{
		waitpid(shell->children[i++], &child_process, 0);
		if (WIFEXITED(child_process))
			shell->exit = WEXITSTATUS(child_process);
	}
}

static void	close_pipes(t_data *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count - 1)
	{
		if (shell->pipes[i][0] > 2)
			close(shell->pipes[i][0]);
		if (shell->pipes[i][1] > 2)
			close(shell->pipes[i][1]);
		i++;
	}
}

void	fork_child(t_data *shell, int i)
{
	int	fd[2];

	if (check_permission(shell->children, shell->cmds[i][0], i))
		shell->children[i] = fork();
	if (shell->children[i] == 0)
	{
		get_fd(shell, i, fd);
		if (fd[0] != STDIN_FILENO && dup2(fd[0], STDIN_FILENO) == -1)
			ft_exit(shell, "pipe(error)");
		if (fd[1] != STDOUT_FILENO && dup2(fd[1], STDOUT_FILENO) == -1)
			ft_exit(shell, "pipe(error)");
		close_pipes(shell);
		execve(shell->executable_paths[i], shell->cmds[i], shell->envp);
		ft_exit(shell, "execve");
	}
	else if (shell->children[i] == -1)
		ft_exit(shell, "pipe(error)");
	else
	{
		if (i > 0)
			close(shell->pipes[i - 1][0]);
		if (i != shell->cmd_count - 1)
			close(shell->pipes[i][1]);
	}
}
