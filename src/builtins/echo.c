/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:46:17 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/25 16:08:17 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char **cmds)
{
	int	i;
	int	return_flag;

	i = 0;
	return_flag = 1;
	if (cmds[1] && ft_strcmp(cmds[1], "-n") == 0)
	{
		return_flag = 0;
		i++;
	}
	while (cmds[++i])
	{
		ft_putstr_fd(cmds[i], STDOUT_FILENO);
		if (cmds[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (return_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	print_export(t_data *shell)
{
	t_env	*iterator;

	iterator = shell->env;
	while (iterator)
	{
		ft_putstr_fd("declare -x ", shell->fd_out);
		ft_putstr_fd(iterator->name, shell->fd_out);
		ft_putstr_fd("=", shell->fd_out);
		ft_putstr_fd(iterator->value, shell->fd_out);
		ft_putstr_fd("\n", shell->fd_out);
		iterator = iterator->next;
	}
}
