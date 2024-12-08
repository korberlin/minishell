/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 14:49:24 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/24 13:39:41 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_name_valid(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (NO);
	if (ft_isdigit(cmd[0]))
		return (NO);
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (NO);
		i++;
	}
	return (YES);
}

void	ft_env(t_data *shell)
{
	t_env	*iterator;

	iterator = shell->env;
	while (iterator)
	{
		ft_putstr_fd(iterator->name, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(iterator->value, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		iterator = iterator->next;
	}
}

void	ft_pwd(t_data *shell, char **cmds)
{
	char	current[1024];

	if (cmds[1])
		return (ft_err(shell, "toomany"));
	ft_putstr_fd(getcwd(current, sizeof(current)), STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	free_iterator(t_env *iterator)
{
	free(iterator->name);
	free(iterator->value);
	free(iterator);
}

void	unset_2(t_data *shell, char *cmds, t_env *iterator)
{
	t_env	*prev;

	prev = NULL;
	while (iterator)
	{
		if (!ft_strcmp(iterator->name, cmds))
		{
			if (ft_strcmp(cmds, "PATH") == 0)
				shell->paths = NULL;
			if (prev == NULL)
				shell->env = iterator->next;
			else
				prev->next = iterator->next;
			free_iterator(iterator);
			if (prev == NULL)
				iterator = shell->env;
			else
				iterator = prev->next;
		}
		else
		{
			prev = iterator;
			iterator = iterator->next;
		}
	}
}
