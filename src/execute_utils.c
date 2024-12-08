/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:41:13 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/25 13:35:53 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_permission(pid_t *children, char *cmd, int i)
{
	if (ft_strcmp(cmd, ".") == 0
		|| ft_strcmp(cmd, "..") == 0
		|| ft_strcmp(cmd, "./") == 0)
	{
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		children[i] = -2;
		return (NO);
	}
	return (YES);
}

int	exec_builtin(t_data *shell, int i)
{
	int	temp[2];
	int	fd[2];

	if (!backup(shell, i, fd, temp))
		return (FAIL);
	start_builtin(shell, shell->cmds[i]);
	if (shell->err_status)
		return (FAIL);
	restore(shell, i, fd, temp);
	shell->exit = FAIL;
	return (YES);
}

int	is_builtin(char *command)
{
	if (ft_strncmp("echo", command, 4) == 0)
		return (1);
	else if (ft_strncmp("cd", command, 2) == 0)
		return (1);
	else if (ft_strncmp("pwd", command, 3) == 0)
		return (1);
	else if (ft_strncmp("export", command, 6) == 0)
		return (1);
	else if (ft_strncmp("unset", command, 5) == 0)
		return (1);
	else if (ft_strncmp("env", command, 3) == 0)
		return (1);
	else if (ft_strncmp("exit", command, 4) == 0)
		return (1);
	return (0);
}

void	start_builtin(t_data *shell, char **cmds)
{
	if (cmds[0])
	{
		if (ft_strcmp(cmds[0], "exit") == 0)
			ft_quit(shell);
		if (ft_strcmp(cmds[0], "cd") == 0)
			return (ft_cd(shell, cmds));
		if (ft_strcmp(cmds[0], "pwd") == 0)
			return (ft_pwd(shell, cmds));
		if (ft_strcmp(cmds[0], "echo") == 0)
			return (ft_echo(cmds));
		if (ft_strcmp(cmds[0], "env") == 0)
			return (ft_env(shell));
		if (ft_strcmp(cmds[0], "unset") == 0)
			return (ft_unset(shell, cmds, 0));
		if (ft_strcmp(cmds[0], "export") == 0)
			return (ft_export(shell, cmds));
	}
	shell->err_status = FAIL;
}

void	handle_child_processes(t_data *shell)
{
	int	i;

	shell->children = ft_calloc(sizeof(pid_t), shell->cmd_count);
	if (!shell->children)
		ft_exit(shell, "memory");
	i = 0;
	while (i < shell->cmd_count)
	{
		if (is_builtin(shell->cmds[i][0]))
		{
			if (!exec_builtin(shell, i))
			{
				shell->err_status = FAIL;
				return ;
			}
		}
		else
		{
			fork_child(shell, i);
		}
		i++;
	}
}
