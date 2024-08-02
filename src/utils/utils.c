/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:34:53 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/02 17:11:43 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(void *cmd_ptr)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_ptr;
	if (cmd->full_command)
		ft_free_2d_array(&cmd->full_command);
	if (cmd->command_path)
		free(cmd->command_path);
	free(cmd);
}

// not used but maybe used later!
void	free_mini(t_mini *mini)
{
	if (mini->current_dir != NULL)
		free(mini->current_dir);
	if (mini->envp != NULL)
		ft_free_2d_array(&mini->envp);
	if (mini->node != NULL)
		ft_lstclear(&mini->node, free_cmd);
			// Use free_cmd to free the content of each node
	free(mini);
}
