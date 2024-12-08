/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:24:35 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/25 15:51:37 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	adjust_command_count(t_token *iterator, t_data *shell)
{
	while (iterator)
	{
		if (iterator->token[0] == '<' && iterator->token[1] == '<')
		{
			heredoc_delimiter(iterator, shell);
			shell->cmd_count -= 2;
		}
		else if (iterator->token[0] == '>' && iterator->token[1] == '>')
			shell->cmd_count -= 2;
		else if (iterator->token[0] == '<' || iterator->token[0] == '>')
		{
			if (iterator->token[0] == '>')
				shell->truncate = 1;
			shell->cmd_count -= 2;
		}
		else if (iterator->token[0] == '|')
			shell->cmd_count--;
		iterator = iterator->next;
	}
}

void	handle_operator(t_data *shell, t_token **iterator)
{
	if (!iterator || !*iterator)
	{
		shell->err_status = FAIL;
		return ;
	}
	if ((*iterator)->token[0] == '|')
		;
	else if ((*iterator)->token[0] == '<' && (*iterator)->token[1] == '<')
	{
		handle_heredoc(shell);
		if (shell->err_status)
			return ;
	}
	else if ((*iterator)->token[0] == '<' && (*iterator)->next)
		shell->std_input = ft_strdup((*iterator)->next->token);
	else if ((*iterator)->token[0] == '>' && (*iterator)->next)
		handle_output_redirection(shell, iterator);
	if (((*iterator)->token[0] == '>' || (*iterator)->token[0] == '<')
		&& (*iterator)->next)
		*iterator = (*iterator)->next;
	return ;
}

void	store_commands(t_data *shell, t_token *iterator)
{
	int	i;

	i = 0;
	iterator = shell->tokens;
	while (iterator)
	{
		if (is_operator(iterator->token[0]))
		{
			handle_operator(shell, &iterator);
			if (shell->err_status)
				return ;
		}
		else
			shell->cmds[i++] = parse_commands(shell, iterator->token);
		iterator = iterator->next;
	}
	shell->cmds[i] = NULL;
}

char	**parse_commands(t_data *shell, const char *token)
{
	unsigned int	i;
	unsigned int	wc;
	int				len;
	char			**command;

	i = 0;
	wc = count_wc(token);
	command = malloc((wc + 1) * sizeof(char *));
	if (!command)
		ft_exit(shell, "memory");
	while (i < wc)
	{
		while (*token && *token == ' ')
			token++;
		if (*token && *token != ' ')
		{
			len = quote_length(token);
			command[i] = ft_substr(token, 0, len);
			token += len;
		}
		i++;
	}
	command[i] = NULL;
	return (command);
}

void	parser(t_data *shell)
{
	t_token		*iterator;

	iterator = shell->tokens;
	shell->cmd_count = ft_tokensize(shell->tokens);
	adjust_command_count(iterator, shell);
	if (shell->cmd_count < 0)
	{
		ft_err(shell, "command");
		return ;
	}
	shell->cmds = ft_calloc((sizeof(char **)), shell->cmd_count + 1);
	if (!shell->cmds)
		ft_exit(shell, "memory");
	store_commands(shell, iterator);
	if (shell->err_status)
		return ;
	expander(shell);
	return ;
}
