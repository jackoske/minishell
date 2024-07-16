/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:42:10 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/16 11:45:22 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_command_parts(t_cmd *cmd)
{
	int	j;

	j = 0;
	if (cmd && cmd->full_command)
	{
		while (cmd->full_command[j])
		{
			printf("Command Part[%d]: %s\n", j, cmd->full_command[j]);
			j++;
		}
	}
}

void	debug_tokenized_input(char **tokenized_input)
{
	int	j;

	j = 0;
	while (tokenized_input[j])
	{
		printf("Tokenized Input[%d]: %s\n", j, tokenized_input[j]);
		j++;
	}
}
