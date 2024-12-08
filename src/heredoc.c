/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:09:30 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/25 16:06:49 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_heredoc(t_data *shell)
{
	int	fd;

	shell->heredoc_mode = 1;
	fd = open(shell->heredoc_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		ft_exit(shell, "file");
	return (fd);
}

void	handle_heredoc(t_data *shell)
{
	char	*line;
	int		fd;

	fd = open_heredoc(shell);
	handle_signals(shell);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || g_heredoc || is_delimiter(shell, line))
			break ;
		write(fd, line, strlen(line));
		free(line);
	}
	handle_signals(shell);
	close(fd);
	handle_heredoc_2(shell, line);
}

void	handle_heredoc_2(t_data *shell, char *line)
{
	if (!(line))
		ft_putstr_fd("\nwarning: heredoc delimited by end-of-file\n", 1);
	else
		free(line);
	if (g_heredoc)
	{
		write(1, "\n", 1);
		ft_err(shell, "none");
	}
	return ;
}

int	is_delimiter(t_data *shell, char *str)
{
	t_heredoc	*iter;
	char		*deli;

	iter = shell->delimiters;
	deli = iter->delimiters;
	if (str[0] == '\n')
		return (NO);
	if (!ft_strncmp(str, deli, ft_strlen(str) -1))
	{
		shell->delimiters = iter->next;
		return (YES);
	}
	else
		return (NO);
}

void	heredoc_delimiter(t_token *iterator, t_data *shell)
{
	t_heredoc	*new;

	if (iterator->next != NULL)
	{
		new = heredoc_new(iterator);
		if (new)
			heredoc_add_back(&shell->delimiters, new);
	}
	else
		ft_exit(shell, "delimiter");
}
