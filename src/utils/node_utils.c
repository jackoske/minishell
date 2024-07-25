/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:09 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/16 14:33:40 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	printf("Command Path: %s\n",
		cmd->command_path ? cmd->command_path : "NULL");
	if (cmd->full_command)
	{
		printf("Full Command: ");
		for (int i = 0; cmd->full_command[i]; i++)
			printf("%s ", cmd->full_command[i]);
		printf("\n");
	}
	printf("FD In: %d\n", cmd->fd_in);
	printf("FD Out: %d\n", cmd->fd_out);
	printf("Is Heredoc: %d\n", cmd->is_heredoc);
	printf("Is Append: %d\n", cmd->is_append);
	printf("Is Outfile: %d\n", cmd->is_outfile);
	
	printf("Exit Status: %d\n", cmd->mini->exit_status);
}

void	print_nodes(t_list *node)
{
	if (!node)
	{
		printf("No nodes to print\n");
		return ;
	}
	while (node)
	{
		print_cmd((t_cmd *)node->content);
		node = node->next;
		if (node)
			printf("----------\n");
	}
}
