/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azsonmez <azsonmez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:10:34 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/17 13:26:05 by azsonmez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_output_redirection(t_data *shell, t_token **iterator)
{
	if (shell->std_output)
		free(shell->std_output);
	shell->std_output = ft_strdup((*iterator)->next->token);
	if ((*iterator)->token[1] == '>')
		shell->fd_out = open(shell->std_output, O_CREAT | \
		O_WRONLY | O_APPEND, 0644);
	else
		shell->fd_out = open(shell->std_output, O_CREAT | \
		O_WRONLY | O_TRUNC, 0644);
	close(shell->fd_out);
}

int	ft_tokensize(t_token *token)
{
	int		size;
	t_token	*lst;

	lst = token;
	size = 0;
	if (!lst)
		return (size);
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

unsigned int	count_wc(char const *token)
{
	unsigned int	wc;
	bool			sq;
	bool			dq;

	sq = false;
	dq = false;
	wc = 0;
	while (*token)
	{
		while (*token && *token == ' ')
			token++;
		if (*token && *token != ' ')
			wc++;
		while (*token && (*token != ' ' || sq || dq))
		{
			if (*token == '\'' && !dq)
				sq = !sq;
			else if (*token == '"' && !sq)
				dq = !dq;
			token++;
		}
	}
	return (wc);
}

unsigned int	quote_length(char const *token)
{
	unsigned int	len;
	bool			sq;
	bool			dq;

	sq = false;
	dq = false;
	len = 0;
	while (token[len] && (token[len] != ' ' || sq || dq))
	{
		if (token[len] == '\'' && !dq)
			sq = !sq;
		else if (token[len] == '"' && !sq)
			dq = !dq;
		len++;
	}
	return (len);
}

char	*find_next(const char *str)
{
	const char	*c;

	c = str;
	while (*c)
	{
		if (*c == '$' && *(c + 1) != '\0' && (ft_isalnum(*(c + 1))
				|| *(c + 1) == '_' || *(c + 1) == '?'))
			return ((char *)c);
		c++;
	}
	return (NO);
}
