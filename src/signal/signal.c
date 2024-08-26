/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:30:14 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/15 12:27:07 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_mini->signals.sigint_received = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		if (!g_mini->signals.is_executing_command)
			rl_redisplay();
	}
	else if (signal == SIGQUIT && g_mini->signals.is_executing_command)
	{
		write(STDOUT_FILENO, "\nQuit\n", 6);
		// free_mini(&g_mini);
		exit(131);
	}
	// else if (signal == SIGQUIT)
	// {
	// 	// write(STDOUT_FILENO, PROMPT, 11);
	// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");

	// 	rl_replace_line("", 0);
	// 	rl_on_new_line();

	// 	// write(STDOUT_FILENO, "\nQuit\n", 6);
	// 	// free_mini(&g_mini);
	// }
}

void	setup_signal_handlers_exec(void)
{
	signal(SIGINT, handle_signal);
	// signal(SIGQUIT, handle_signal);
	signal(SIGQUIT, SIG_IGN);

}

void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
