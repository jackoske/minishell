/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:53:09 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 12:46:49 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_cmd(t_cmd *cmd)
// {
// 	int	i;

// 	if (!cmd)
// 		return ;
// 	if (cmd->command)
// 		printf("Command: %s\n", cmd->command);
// 	if (cmd->full_command)
// 	{
// 		printf("Full Command: ");
// 		i = 0;
// 		while (cmd->full_command[i])
// 		{
// 			printf("%s ", cmd->full_command[i]);
// 			i++;
// 		}
// 		printf("\n");
// 	}
// 	printf("FD In: %d\n", cmd->fd_in);
// 	printf("FD Out: %d\n", cmd->fd_out);
// 	printf("Is Heredoc: %d\n", cmd->is_heredoc);
// 	printf("Is Append: %d\n", cmd->is_append);
// 	printf("Is Outfile: %d\n", cmd->is_outfile);
// 	printf("Exit Status: %d\n", cmd->mini->exit_status);
// }

// void	print_nodes(t_list *node)
// {
// 	if (!node)
// 	{
// 		printf("No nodes to print\n");
// 		return ;
// 	}
// 	while (node)
// 	{
// 		print_cmd((t_cmd *)node->content);
// 		node = node->next;
// 		if (node)
// 			printf("----------\n");
// 	}
// }
