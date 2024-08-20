/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:21:00 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/20 15:27:42 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_cmd	*initialize_command(void)
// {
// 	t_cmd	*cmd;

// 	cmd = init_cmd();
// 	if (!cmd)
// 		return (NULL);
// 	cmd->full_command = ft_calloc(1, sizeof(char *));
// 	if (!cmd->full_command)
// 	{
// 		free(cmd);
// 		return (NULL);
// 	}
// 	return (cmd);
// }

// static int	validate_command(t_cmd *cmd)
// {
// 	if (cmd->fd_in == -1 || cmd->fd_out == -1)
// 	{
// 		free_cmd(cmd);
// 		return (0);
// 	}
// 	return (1);
// }

// static char	**process_token(t_cmd *cmd, char **tokenized_input)
// {
// 	char	**new_array;

// 	if (is_redirection(*tokenized_input))
// 		process_redirections(cmd, &tokenized_input);
// 	else
// 	{
// 		new_array = ft_add_row_2d_array(cmd->full_command,
// 				ft_remove_paired_quotes(*tokenized_input), 0);
// 		if (!new_array)
// 		{
// 			free_cmd(cmd);
// 			return (NULL);
// 		}
// 		cmd->full_command = new_array;
// 	}
// 	return (tokenized_input + 1);
// }

// t_cmd	*create_command_node(char **tokenized_input)
// {
// 	t_cmd	*cmd;

// 	ft_print_2d_array_fd(tokenized_input, 1);
// 	cmd = initialize_command();
// 	if (!cmd)
// 		return (NULL);
// 	printf("tokenized_input: %s %c\n", *tokenized_input, **tokenized_input);
// 	while (*tokenized_input && **tokenized_input != '|')
// 	{
// 		tokenized_input = process_token(cmd, tokenized_input);
// 		if (!tokenized_input)
// 			return (NULL);
// 	}
// 	if (!validate_command(cmd))
// 		return (NULL);
// 	return (cmd);
// }

// t_list	*create_commands(char **tokenized_input)
// {
// 	t_list	*commands;
// 	t_cmd	*cmd;

// 	while (*tokenized_input)
// 	{
// 		cmd = create_command_node(tokenized_input);
// 		if (!cmd)
// 		{
// 			while (*tokenized_input && **tokenized_input != '|')
// 				tokenized_input++;
// 			if (*tokenized_input)
// 				tokenized_input++;
// 			continue ;
// 		}
// 		ft_lstadd_back(&commands, ft_lstnew(cmd));
// 		while (*tokenized_input && **tokenized_input != '|')
// 			tokenized_input++;
// 		if (*tokenized_input)
// 			tokenized_input++;
// 	}
// 	return (commands);
// }
