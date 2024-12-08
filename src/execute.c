/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoksal <gkoksal@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:40:54 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/25 16:07:17 by gkoksal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_data *shell)
{
	check_commands(shell);
	if (shell->err_status)
		return ;
	reset_pipes(shell);
	handle_redirs(shell);
	if (shell->err_status)
		return ;
	handle_child_processes(shell);
	if (shell->err_status)
		return ;
	wait_children(shell);
}
