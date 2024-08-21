/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:21:00 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 17:07:33 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_command(t_cmd *cmd)
{
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
	{
		free_cmd(cmd);
		return (0);
	}
	return (1);
}

static char	**process_command(t_cmd *cmd, char **tokenized_input)
{
	char	**new_array;

	new_array = ft_add_row_2d_array(cmd->full_command, *tokenized_input, 0);
	if (!new_array)
	{
		free_cmd(cmd);
		return (NULL);
	}
	cmd->full_command = new_array;
	return (tokenized_input + 1);
}

static char	**process_token(t_cmd *cmd, char **tokenized_input,
		int *error_status)
{
	if (is_redirection(ft_remove_paired_quotes(*tokenized_input)))
	{
		*error_status = process_redirections(cmd, &tokenized_input);
		if (*error_status)
			return (NULL);
		return (tokenized_input);
	}
	else
		return (process_command(cmd, tokenized_input));
}

t_cmd	*create_command_node(char **tokenized_input)
{
	t_cmd	*cmd;
	int		error_status;

	error_status = 0;
	cmd = initialize_command();
	if (!cmd)
		return (NULL);
	while (*tokenized_input && **tokenized_input != '|')
	{
		tokenized_input = process_token(cmd, tokenized_input, &error_status);
		if (error_status)
		{
			free_cmd(cmd);
			return (NULL);
		}
		if (!tokenized_input)
			return (NULL);
	}
	if (!validate_command(cmd))
		return (NULL);
	return (cmd);
}

t_list	*create_commands(char **tokenized_input)
{
	t_list	*commands;
	t_cmd	*cmd;

	commands = NULL;
	while (*tokenized_input)
	{
		cmd = create_command_node(tokenized_input);
		if (!cmd)
		{
			while (*tokenized_input && **tokenized_input != '|')
				tokenized_input++;
			if (*tokenized_input)
				tokenized_input++;
			continue ;
		}
		ft_lstadd_back(&commands, ft_lstnew(cmd));
		while (*tokenized_input && **tokenized_input != '|')
			tokenized_input++;
		if (*tokenized_input)
			tokenized_input++;
	}
	return (commands);
}
