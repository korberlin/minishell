/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:48:07 by azsonmez          #+#    #+#             */
/*   Updated: 2024/07/25 14:06:44 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	free_3d(char ***cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free_2d(cmd[i++]);
	free(cmd);
}

void	free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_tokens(t_token **tokens, void (*del)(void*))
{
	t_token	*temp;
	t_token	*next;

	if (!tokens || !del)
		return ;
	temp = *tokens;
	while (temp != NULL)
	{
		next = temp->next;
		(*del)(temp->token);
		free(temp);
		temp = next;
	}
	*tokens = NULL;
}

void	free_delimiters(t_data *shell)
{
	t_heredoc	*new;
	t_heredoc	*temp;

	new = shell->delimiters;
	while (new->next)
	{
		free(new->delimiters);
		temp = new;
		new = new->next;
		free(temp);
	}
	free(new->delimiters);
	free(new);
}
