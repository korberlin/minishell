/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 16:28:53 by azsonmez          #+#    #+#             */
/*   Updated: 2024/07/25 16:14:05 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_quit(t_data *shell)
{
	int	i;

	check_exit_args(shell);
	free_env(shell->env);
	free_shell(shell);
	i = shell->exit;
	free(shell);
	exit(i);
}

void	check_exit_args(t_data *shell)
{
	int	i;
	int	arg_count;

	i = -1;
	while (++i < shell->cmd_count)
	{
		arg_count = 0;
		if (!ft_strcmp("exit", shell->cmds[i][0]))
		{
			while (shell->cmds[i][arg_count])
				arg_count++;
			break ;
		}
	}
	if (arg_count > 2)
	{
		shell->exit = 2;
		ft_err(shell, "numeric");
		return ;
	}
	if (arg_count == 2)
		handle_exit_code(shell, shell->cmds[i][1]);
}

void	handle_exit_code(t_data *shell, char *arg)
{
	int	exit_code;
	int	i;

	i = 0;
	if ((arg[0] == '-' || arg[0] == '+') && arg[1] != '\0')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			shell->exit = 2;
			ft_err(shell, "numeric");
			exit(shell->exit);
		}
		i++;
	}
	exit_code = ft_atoi(arg);
	shell->exit = exit_code % 256;
}
