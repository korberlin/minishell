/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:52:05 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/24 13:40:14 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_slash(char **temp)
{
	int		i;
	char	**paths;
	int		len;

	len = 0;
	while (temp[len])
		len++;
	paths = malloc(sizeof(char *) * (len + 1));
	if (!paths)
		return (NULL);
	i = -1;
	while (temp[++i])
	{
		paths[i] = ft_strjoin(temp[i], "/");
		if (!paths[i])
			return (NULL);
	}
	paths[i] = NULL;
	free_2d(temp);
	return (paths);
}

bool	check_path_exists(t_data *shell)
{
	t_env	*iterator;

	iterator = shell->env;
	while (iterator)
	{
		if (ft_strcmp(iterator->name, "PATH") == 0)
			return (true);
		iterator = iterator->next;
	}
	return (false);
}

void	fill_paths(t_data *shell)
{
	t_env	*iterator;
	char	**temp;

	if (!shell->env)
		return ;
	if (!check_path_exists(shell))
	{
		shell->paths = NULL;
		return ;
	}
	iterator = shell->env;
	while (iterator)
	{
		if (ft_strcmp(iterator->name, "PATH") == 0)
		{
			temp = ft_split(iterator->value, ':');
			if (!temp)
				ft_err(shell, "memory");
		}
		iterator = iterator->next;
	}
	shell->paths = add_slash(temp);
	if (!shell->paths)
		ft_err(shell, "memory");
}

void	reset_shell(t_data *shell)
{
	g_heredoc = 0;
	shell->tokens = 0;
	shell->interactive = 1;
	shell->pipe_count = 0;
	shell->err_status = 0;
	shell->fd_inf = 0;
	shell->fd_out = 0;
	shell->cmds = 0;
	shell->executable_paths = 0;
	shell->cmd_count = 0;
	shell->truncate = 0;
	shell->input = 0;
	shell->std_input = 0;
	shell->std_output = 0;
	shell->pipes = 0;
	shell->children = 0;
	shell->heredoc_mode = 0;
	shell->heredoc_file = ".temp";
	shell->delimiters = 0;
	fill_paths(shell);
}

void	reset_pipes(t_data *shell)
{
	int	i;

	if (shell->cmd_count <= 0)
		return ;
	shell->pipes = malloc(sizeof(int *) * (shell->cmd_count + 1));
	if (!shell->pipes)
		ft_exit(shell, "pipe(error)");
	i = -1;
	while (++i < shell->cmd_count -1)
	{
		shell->pipes[i] = malloc(sizeof(int) * 2);
		if (!shell->pipes[i])
			ft_exit(shell, "memory");
		if (pipe(shell->pipes[i]) == -1)
			ft_exit(shell, "pipe(error)");
	}
}
