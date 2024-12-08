/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:53:48 by azsonmez          #+#    #+#             */
/*   Updated: 2024/07/24 15:19:21 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	name_len(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

t_env	*add_env(char *env, char *separator)
{
	t_env	*new_env;
	int		len;
	char	*name;
	char	*value;

	len = name_len(env);
	name = ft_substr(env, 0, len);
	value = separator + 1;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
	{
		free(name);
		return (NULL);
	}
	new_env->name = ft_strdup(name);
	new_env->value = ft_strdup(value);
	new_env->next = NULL;
	free(name);
	return (new_env);
}

void	append_env(t_data *shell, char *variable)
{
	t_env	*iterator;
	t_env	*new;
	char	*seperator;

	seperator = ft_strchr(variable, '=');
	new = add_env(variable, seperator);
	if (!new)
		return (ft_err(shell, "memory"));
	iterator = shell->env;
	while (iterator->next)
		iterator = iterator->next;
	iterator->next = new;
}

t_env	*create_env(char **env)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;
	char	*separator;

	head = NULL;
	tail = NULL;
	i = -1;
	while (env[++i])
	{
		separator = ft_strchr(env[i], '=');
		if (separator)
		{
			new_node = add_env(env[i], separator);
			if (!head)
				head = new_node;
			else
				tail->next = new_node;
			tail = new_node;
		}
	}
	return (head);
}

char	*get_env(t_data *shell, char *var_name)
{
	t_env	*iterator;

	iterator = shell->env;
	while (iterator)
	{
		if (ft_strcmp(iterator->name, var_name) == 0)
			return (iterator->value);
		iterator = iterator->next;
	}
	return (NULL);
}
