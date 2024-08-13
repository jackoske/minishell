/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:23:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 12:42:27 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*handle_redirection(t_cmd *node, char **full_command, int **i,
		int mode)
{
	int	fd;

	fd = get_fd(node->fd_out, NULL, full_command[++(**i)], mode);
	if (mode == 1)
		fd = get_fd(node->fd_in, NULL, full_command[++(**i)], mode);
	if (fd == -1)
	{
		**i = -2;
		if (mode == 1)
			node->fd_in = -1;
		else
			node->fd_out = -1;
		return (node);
	}
	if (mode == 1)
		node->fd_in = fd;
	else
		node->fd_out = fd;
	return (node);
}

static t_cmd	*get_redir_heredoc(t_cmd *node, char **full_command, int **i)
{
	if (!full_command[++(**i)])
	{
		**i = -2;
		node->fd_in = -1;
		ft_error(1, NULL);
		return (node);
	}
	node->fd_in = get_here_doc(full_command[(*(*i))],
			"minishell: warning: here-document delimited by end-of-file");
	if (node->fd_in == -1)
	{
		**i = -2;
		node->fd_in = -1;
	}
	node->is_heredoc = 1;
	return (node);
}

t_cmd	*handle_redirections(t_cmd *node, char *input, char **full_command,
		int *i)
{
	if (input[0] == '>' && input[1] == '>')
		node = handle_redirection(node, full_command, &i, 3);
	else if (input[0] == '>')
		node = handle_redirection(node, full_command, &i, 2);
	else if (input[0] == '<' && input[1] == '<')
		node = get_redir_heredoc(node, full_command, &i);
	else if (input[0] == '<')
		node = handle_redirection(node, full_command, &i, 1);
	return (node);
}

t_cmd	*handle_non_redir_commands(t_cmd *node, char *input)
{
	if (!is_string_quoted(input))
		node->full_command = ft_add_row_2d_array(node->full_command, input, 0);
	else
		node->full_command = ft_add_row_2d_array(node->full_command,
				ft_remove_paired_quotes(input), 0);
	return (node);
}

t_cmd	*set_redir(t_cmd *node, char *input, char **full_command, int *i)
{
	if (input[0])
	{
		if (input[0] == '>' || input[0] == '<')
			node = handle_redirections(node, input, full_command, i);
		else if (input[0] != '|')
			node = handle_non_redir_commands(node, input);
	}
	if (node->fd_in == -1 || node->fd_out == -1)
	{
		ft_free_2d_array(&node->full_command);
		free(node);
		return (NULL);
	}
	return (node);
}
