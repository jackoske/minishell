/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/22 14:17:44 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_loop(void)
{
	char	*input;

	while (1)
	{
		setup_signal_handlers();
		if (g_mini->signals.sigint_received)
		{
			g_mini->signals.sigint_received = 0;
			continue ;
		}
		input = readline(PROMPT);
		if (input == NULL)
			break ;
		if (input[0] != '\0')
			add_history(input);
		else
		{
			free(input);
			continue ;
		}
		g_mini->signals.is_executing_command = 1;
		setup_signal_handlers_exec();
		handle_input(input);
		g_mini->signals.is_executing_command = 0;
	}
}
