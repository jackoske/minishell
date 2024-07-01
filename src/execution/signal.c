/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 13:30:14 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/28 14:44:30 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_sigint_received = 0;

void free_mini(t_mini *mini)
{
    if (mini->current_dir != NULL)
        free(mini->current_dir);
    if (mini->envp != NULL)
        ft_free_2d_array(&mini->envp);
    if (mini->node != NULL)
        ft_lstclear(&mini->node, free);
    free(mini);
}

void handle_sigint(int sig) {
    (void)sig;
    g_sigint_received = 1;
    write(STDOUT_FILENO, "\nminishell> ", 12);
}

//void setup_signal_handlers(void) {
//    struct sigaction sa;
//
//    sa.sa_handler = handle_sigint;
//    sa.sa_flags = SA_RESTART;
//    sigemptyset(&sa.sa_mask);
//    sigaction(SIGINT, &sa, NULL);
//}

static void handle_signal(int signal)
{
    if (signal == SIGINT)
    {
        // Handle SIGINT (Ctrl+C)
        write(STDOUT_FILENO, "\n", 1); // Move to a new line
        rl_on_new_line();              // Tell readline that the cursor is now on a new line
        rl_replace_line("", 0);        // Clear the current input
        rl_redisplay();                // Redisplay the prompt
    }
    else if (signal == SIGQUIT)
    {
        // Handle SIGQUIT (Ctrl+\)
        write(STDOUT_FILENO, "\nQuit\n", 6);
    }
}

void setup_signal_handlers()
{
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);
}
