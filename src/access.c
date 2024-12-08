/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:33:39 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/24 15:44:27 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_absolute(t_data *shell, char *str)
{
	if (access(str, F_OK) == 0)
	{
		add_executable_paths(shell, str);
		return (SUCCESS);
	}
	return (FAIL);
}

int	check_access(t_data *shell, char **command)
{
	int		tracker;
	int		j;

	tracker = 0;
	j = -1;
	if (!add_absolute(shell, *command))
		return (SUCCESS);
	if (!shell->paths)
		return (FAIL);
	if (loop_command_paths(shell, command, &tracker))
		return (FAIL);
	if (tracker > 0)
		return (SUCCESS);
	return (FAIL);
}

int	loop_command_paths(t_data *shell, char **command, int *tracker)
{
	int		j;
	char	*full_name;

	j = -1;
	while (shell->paths[++j])
	{
		full_name = ft_strjoin(shell->paths[j], *command);
		if (!full_name)
		{
			ft_err(shell, "memory");
			return (FAIL);
		}
		if (access(full_name, F_OK) == 0)
		{
			*tracker = *tracker + 1;
			add_executable_paths(shell, full_name);
			free(full_name);
			break ;
		}
		free(full_name);
	}
	return (SUCCESS);
}

int	check_cwd_access(t_data *shell, char **command)
{
	char	*pwd;
	char	*full_name;

	if (access(*command, F_OK) == 0)
	{
		add_executable_paths(shell, *command);
		return (SUCCESS);
	}
	pwd = ft_strdup(get_env(shell, "PWD"));
	full_name = ft_strjoin(pwd, *command);
	if (!pwd || !full_name)
	{
		ft_err(shell, "memory");
		return (FAIL);
	}
	free(pwd);
	if (access(full_name, F_OK) == 0)
	{
		free(full_name);
		return (SUCCESS);
	}
	free(full_name);
	return (FAIL);
}

void	check_commands(t_data *shell)
{
	int	i;

	i = -1;
	while (++i < shell->cmd_count)
	{
		if (check_access(shell, shell->cmds[i])
			&& check_cwd_access(shell, shell->cmds[i])
			&& !is_builtin(shell->cmds[i][0]))
		{
			ft_err(shell, "command");
			return ;
		}
	}
	return ;
}
