/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:30:14 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/19 14:20:44 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;
volatile sig_atomic_t	g_is_executing_command = 0;

static void handle_signal(int signal)
{
    if (signal == SIGINT)
    {
        if (g_is_executing_command)
        {
            // Handling SIGINT during command execution
            write(STDOUT_FILENO, "\n", 1);
        }
        else
        {
            // Handling SIGINT during readline
            g_sigint_received = 1;
            write(STDOUT_FILENO, "\n", 1);
            rl_replace_line("", 0);
            rl_on_new_line();
            rl_redisplay();
        }
    }
    else if (signal == SIGQUIT)
    {
        if (g_is_executing_command)
        {
            write(STDOUT_FILENO, "\nQuit\n", 6);
        }
    }
}


void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
