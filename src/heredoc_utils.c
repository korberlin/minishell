/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:57:26 by azsonmez          #+#    #+#             */
/*   Updated: 2024/07/25 16:07:53 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*heredoc_new(t_token *iterator)
{
	t_heredoc	*new_node;

	if (iterator->next)
	{
		new_node = malloc(sizeof(t_heredoc));
		if (!new_node)
			return (NULL);
		new_node->delimiters = ft_strdup(iterator->next->token);
		if (!new_node->delimiters)
			return (NULL);
		new_node->next = NULL;
		return (new_node);
	}
	return (NULL);
}

static t_heredoc	*ft_heredoclast(t_heredoc *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	heredoc_add_back(t_heredoc **lst, t_heredoc *new)
{
	t_heredoc	*last_ptr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_ptr = ft_heredoclast(*lst);
	last_ptr -> next = new;
}
