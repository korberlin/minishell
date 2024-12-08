/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:03:33 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/25 14:05:39 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_shell(t_data *shell)
{
	if (shell->tokens)
		free_tokens(&shell->tokens, free);
	if (shell->delimiters)
		free_delimiters(shell);
	if (shell->cmds)
		free_3d(shell->cmds);
	if (shell->input)
		free(shell->input);
	if (shell->std_input)
		free(shell->std_input);
	if (shell->std_output)
		free(shell->std_output);
	if (shell->paths)
		free_2d(shell->paths);
	if (shell->executable_paths)
		free_2d(shell->executable_paths);
	if (shell->pipes)
		free_pipes(shell, shell->pipes);
	if (shell->children)
		free(shell->children);
	free_shell_2(shell);
}

void	free_shell_2(t_data *shell)
{
	if (shell->heredoc_file)
		unlink(shell->heredoc_file);
	if (shell->fd_inf && shell->fd_inf > 2)
		close(shell->fd_inf);
	if (shell->fd_out && shell->fd_out > 2)
		close(shell->fd_out);
}
