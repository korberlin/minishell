/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 16:56:01 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/25 16:07:30 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	key_value(char *value, t_data *shell, char *cmds)
{
	char	*key;

	key = ft_substr(cmds, 0, value - cmds);
	if (!key)
		ft_exit(shell, "memory");
	ft_unset(shell, &key, 1);
	if (!is_name_valid(key) || cmds[0] == '=')
	{
		free(key);
		shell->exit = 1;
		return (ft_err(shell, "export"));
	}
	else
		append_env(shell, cmds);
	free(key);
}

void	ft_export(t_data *shell, char **cmds)
{
	int		i;
	char	*value;

	i = 0;
	if (!cmds[1])
		return (print_export(shell));
	while (cmds[++i])
	{
		value = ft_strchr(cmds[i], '=');
		if (value)
			key_value(value, shell, cmds[i]);
		else
		{
			if (!is_name_valid(cmds[i]) || ft_isdigit(cmds[i][0]))
			{
				shell->exit = 1;
				return (ft_err(shell, "export"));
			}
		}
	}
}

void	ft_unset(t_data *shell, char **cmds, int j)
{
	int		i;
	t_env	*iterator;

	if (j == 1)
	{
		iterator = shell->env;
		unset_2(shell, cmds[0], iterator);
	}
	else
	{
		i = 0;
		while (cmds[++i])
		{
			iterator = shell->env;
			unset_2(shell, cmds[i], iterator);
		}
	}
}

void	ft_cd(t_data *shell, char **cmds)
{
	char	cwd[1024];
	char	*conservative;
	char	*var;

	if (cmds[1] && cmds[2])
		return (ft_err(shell, "toomany"));
	conservative = old_pwd(shell);
	if (!cmds[1] || ft_strcmp(cmds[1], "~") == 0)
	{
		chdir(getenv("HOME"));
		return ;
	}
	else
	{
		if (chdir(cmds[1]) != 0)
			return (ft_err(shell, "directory"));
	}
	getcwd(cwd, sizeof(cwd));
	var = ft_strjoin("PWD=", cwd);
	ft_unset(shell, (char *[]){"unset", "OLDPWD", NULL}, 0);
	ft_unset(shell, (char *[]){"unset", "PWD", NULL}, 0);
	append_env(shell, conservative);
	append_env(shell, var);
	return ;
}

char	*old_pwd(t_data *shell)
{
	char	*str;
	char	*str2;
	t_env	*iterator;

	iterator = shell->env;
	while (iterator)
	{
		if (!ft_strcmp(iterator->name, "PWD"))
		{
			str = ft_strdup(iterator->value);
			str2 = ft_strjoin("OLDPWD=", str);
			free(str);
			return (str2);
		}
		iterator = iterator->next;
	}
	return (NULL);
}
