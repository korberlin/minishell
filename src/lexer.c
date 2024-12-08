/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:21:11 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/24 12:27:48 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_remaining_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i] && !ft_isspace(str[i]) && !is_operator(str[i]))
		i++;
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (ft_substr(str, 0, i));
}

int	check_quote(bool *sq, bool *dq, char c)
{
	if (c == '\'' && *dq == false)
	{
		*sq = !(*sq);
		return (YES);
	}
	else if (c == '"' && *sq == false)
	{
		*dq = !(*dq);
		return (YES);
	}
	return (NO);
}

void	tokenizer(t_data *shell, char *str, int *len, int *i)
{
	t_token	*final_token;
	char	*next_word;

	append_operators(shell, i, len, str);
	final_token = retrieve_last(shell);
	if (*len > 0 && final_token && (final_token->token[0] == '>'
			|| final_token->token[0] == '<'))
	{
		next_word = get_remaining_word(str + *i);
		*len -= ft_strlen(next_word);
		*i += ft_strlen(next_word);
		append_token(shell, next_word);
	}
	if (*len > 0)
	{
		append_token(shell, ft_substr(str, *i, *len));
		*i += *len;
	}
}

void	lexer(t_data *shell)
{
	bool	sq;
	bool	dq;
	int		i;
	char	*str;
	int		len;

	sq = false;
	dq = false;
	str = shell->input;
	i = 0;
	while (str[i])
	{
		len = 0;
		while (ft_isspace(str[i]))
			i++;
		while ((!is_operator(str[i + len]) || sq || dq) && str[len + i])
			check_quote(&sq, &dq, str[i + len++]);
		tokenizer(shell, str, &len, &i);
	}
	if (sq || dq)
		ft_err(shell, "quote");
}
