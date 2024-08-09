/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/09 17:36:43 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt_loop(void)
{
	char	*input;

	setup_signal_handlers();
	while (1)
	{
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
		handle_input(input);
		g_mini->signals.is_executing_command = 0;
	}
}
