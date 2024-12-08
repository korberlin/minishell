/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azsonmez <azsonmez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 19:01:24 by gkoksal           #+#    #+#             */
/*   Updated: 2024/07/18 16:11:50 by azsonmez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_prompt(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	non_interactive_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)");
		write(1, "\n", 2);
		rl_on_new_line();
	}
}

void	interactive_signals(void)
{
	struct sigaction	sig;
	struct sigaction	sig_ign;

	memset(&sig, 0, sizeof(struct sigaction));
	memset(&sig_ign, 0, sizeof(struct sigaction));
	sig.sa_handler = new_prompt;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig_ign.sa_handler = SIG_IGN;
	sigemptyset(&sig_ign.sa_mask);
	sig_ign.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig_ign, NULL);
}

void	non_interactive_signals(void)
{
	struct sigaction	sig;

	memset(&sig, 0, sizeof(struct sigaction));
	sig.sa_handler = non_interactive_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	handle_signals(t_data *shell)
{
	if (shell->interactive == 1)
	{
		shell->interactive = 0;
		interactive_signals();
	}
	else
	{
		shell->interactive = 1;
		non_interactive_signals();
	}
}
