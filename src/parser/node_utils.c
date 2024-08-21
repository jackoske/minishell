/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:06:03 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 17:07:13 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*initialize_command(void)
{
	t_cmd	*cmd;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	cmd->full_command = ft_calloc(1, sizeof(char *));
	if (!cmd->full_command)
	{
		free(cmd);
		return (NULL);
	}
	return (cmd);
}
