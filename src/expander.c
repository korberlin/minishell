/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:14:51 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/24 15:16:54 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*variable_value(t_data *shell, char *start, int length)
{
	char	*var_name;
	char	*value;

	var_name = ft_substr(start + 1, 0, length);
	if (var_name[0] == '?')
		value = ft_itoa(shell->exit);
	else
		value = ft_strdup(get_env(shell, var_name));
	if (!value)
		value = ft_calloc(sizeof(char *), 1);
	if (!value)
		ft_exit(shell, "memory");
	free(var_name);
	return (value);
}

char	*replace_next_variable(char *result, char *value, char *var_end,
	char *var_start)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(result, 0, var_start - result);
	tmp2 = ft_strjoin(tmp1, value);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, var_end);
	free(tmp2);
	return (tmp1);
}

char	*add_variables(t_data *shell, char **str)
{
	char	*result;
	char	*start;
	char	*end;
	char	*value;
	char	*temp;

	result = ft_strdup(*str);
	free(*str);
	while (find_next(result))
	{
		start = find_next(result);
		end = start + 1;
		if (*end == '?')
			end++;
		else
			while (isalnum(*end) || *end == '_')
				end++;
		value = variable_value(shell, start, end - start - 1);
		temp = result;
		result = replace_next_variable(temp, value, end, start);
		free(temp);
		free(value);
	}
	return (result);
}

void	expander(t_data *shell)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < shell->cmd_count)
	{
		j = 0;
		while (shell->cmds[i][j])
		{
			if (!ft_strchr(shell->cmds[i][j], '\''))
				shell->cmds[i][j] = add_variables(shell, &shell->cmds[i][j]);
			if (ft_strchr(shell->cmds[i][j], '"')
				|| ft_strchr(shell->cmds[i][j], '\''))
			{
				eliminate_quotes(shell->cmds[i][j], &temp);
				if (!temp)
					ft_err(shell, "memory");
				free(shell->cmds[i][j]);
				shell->cmds[i][j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	eliminate_quotes(char *str, char **output)
{
	char		*temp;
	char		*c;
	bool		sq;
	bool		dq;

	sq = false;
	dq = false;
	*output = ft_strdup("");
	while (*str)
	{
		if (*str == '\'' && !dq)
			sq = !sq;
		else if (*str == '"' && !sq)
			dq = !dq;
		else
		{
			c = ft_substr(str, 0, 1);
			temp = ft_strjoin(*output, c);
			free(*output);
			free(c);
			*output = temp;
		}
		str++;
	}
}
