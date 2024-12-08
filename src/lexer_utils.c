/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:36:21 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/08 18:59:16 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(int c)
{
	if (c == '|' || c == '<' || c == '>')
		return (YES);
	return (NO);
}

int	is_multi_char_operator(const char *str)
{
	return ((str[0] == '>' && str[1] == '>')
		|| (str[0] == '<' && str[1] == '<'));
}

void	append_operators(t_data *shell, int *i, int *len, char *str)
{
	if (is_operator(str[*i]))
	{
		if (is_multi_char_operator(&str[*i]))
		{
			append_token(shell, ft_substr(str, *(i), 2));
			*i += 2;
		}
		else
		{
			append_token(shell, ft_substr(str, *i, 1));
			(*i)++;
		}
		*len = 0;
	}
}

t_token	*retrieve_last(t_data *shell)
{
	t_token	*last;

	last = shell->tokens;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

void	append_token(t_data *shell, char *token)
{
	t_token	*new;
	t_token	*last;

	new = malloc(sizeof(t_token));
	if (!new)
		ft_err(shell, "memory");
	new->token = ft_strtrim(token, " \t\n\v\f\r");
	if (!new->token)
		ft_err(shell, "memory");
	new->next = 0;
	free(token);
	if (!(shell->tokens))
	{
		shell->tokens = new;
		return ;
	}
	last = retrieve_last(shell);
	last->next = new;
}
