/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:18:28 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 12:47:19 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->full_command = NULL;
	node->command_path = NULL;
	node->fd_in = 0;
	node->fd_out = 1;
	node->is_heredoc = 0;
	node->is_append = 0;
	node->mini = g_mini;
	return (node);
}

void	init_mini(t_mini *mini)
{
	mini->node = NULL;
	mini->current_dir = NULL;
	mini->exit_status = 0;
	mini->signals.sigint_received = 0;
	mini->signals.is_executing_command = 0;
}
