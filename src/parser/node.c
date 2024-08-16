/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:21:00 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/16 11:39:59 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(const char *token)
{
	if (!token)
		return (0);
	if (strcmp(token, ">") == 0 || strcmp(token, ">>") == 0 || strcmp(token,
			"<") == 0 || strcmp(token, "<<") == 0)
		return (1);
	return (0);
}

t_cmd	*create_command_node(char **tokenized_input, int *i)
{
	t_cmd	*cmd;
	char	**new_array;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	cmd->full_command = ft_calloc(1, sizeof(char *));
	if (!cmd->full_command)
	{
		free(cmd);
		return (NULL);
	}
	while (tokenized_input[*i] && tokenized_input[*i][0] != '|')
	{
		if (is_redirection(tokenized_input[*i]))
		{
			process_redirections(cmd, tokenized_input, i);
		}
		else
		{
			new_array = ft_add_row_2d_array(cmd->full_command,
					tokenized_input[*i], 0);
			if (!new_array)
			{
				free_cmd(cmd);
				return (NULL);
			}
			cmd->full_command = new_array;
		}
		(*i)++;
	}
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

t_list	*create_commands(char **tokenized_input)
{
	t_list	*commands;
	int		i;
	t_cmd	*cmd;

	commands = NULL;
	i = 0;
	while (tokenized_input[i])
	{
		cmd = create_command_node(tokenized_input, &i);
		if (!cmd)
		{
			ft_lstclear(&commands, free_cmd);
			return (NULL);
		}
		ft_lstadd_back(&commands, ft_lstnew(cmd));
		if (tokenized_input[i] && tokenized_input[i][0] == '|')
			i++;
	}
	return (commands);
}
