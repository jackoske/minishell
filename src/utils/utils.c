/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:34:53 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 14:55:31 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to free a t_cmd structure
void	free_cmd(void *cmd_ptr)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)cmd_ptr;
	if (cmd->full_command)
		ft_free_2d_array(&(cmd->full_command));
	if (cmd->command_path)
		free(cmd->command_path);
	free(cmd);
}

// not used but maybe used later!
void	free_mini(t_mini **mini)
{
	if (mini && *mini)
	{
		if ((*mini)->current_dir != NULL)
			free((*mini)->current_dir);
		if ((*mini)->envp != NULL)
			ft_free_2d_array(&(*mini)->envp);
		if ((*mini)->node != NULL)
			ft_lstclear(&(*mini)->node, free_cmd);
		free(*mini);
		*mini = NULL;
	}
}

int	is_all_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}
