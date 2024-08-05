/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:23:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 15:08:02 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Error handling for file access:
- '<' : no such file or directory (F_OK == -1) or permission denied (R_OK == -1)
- '>' : permission denied (W_OK == -1)
- '>>': permission denied (W_OK == -1)
*/
static int	check_access(char *path, int mode)
{
	if (mode == 1) // Read mode
	{
		if (access(path, F_OK) == -1)
			return (ft_error1(3, NULL, 127, NULL), 0);
		else if (access(path, R_OK) == -1)
			return (ft_error1(5, NULL, 1, NULL), 0);
			// return (ft_error(5, NULL), 0);
		return (1);
	}
	else if (mode == 2) // Write mode
	{
		if (access(path, W_OK) == -1 && access(path, F_OK) != -1)
			return (ft_error1(5, NULL, 1, NULL), 0);
			// return (ft_error(5, NULL), 0);
		return (1);
	}
	return (1);
}

static int	get_fd(int oldfd, int mode, char *path)
{
	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (!check_access(path, mode))
		return (-1);
	if (mode == 1)
		return (open(path, O_RDONLY));
	else if (mode == 2)
		return (open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666));
	else if (mode == 3)
		return (open(path, O_WRONLY | O_CREAT | O_APPEND, 0666));
	return (-1);
}

static t_cmd	*handle_redirection(t_cmd *node, char **full_command, int **i,
		int mode)
{
	if (mode == 2 || mode == 3)
	{
		if (node->fd_out > 2)
			close(node->fd_out);
		node->fd_out = get_fd(node->fd_out, mode, full_command[++(**i)]);
		if (node->fd_out == -1)
			**i = -2;
	}
	else if (mode == 1)
	{
		if (node->fd_in > 2)
			close(node->fd_in);
		node->fd_in = get_fd(node->fd_in, mode, full_command[++(**i)]);
		if (node->fd_in == -1)
			**i = -2;
	}
	return (node);
}

static t_cmd	*get_redir_heredoc(t_cmd *node,
		char **full_command, int **i)
{
	if (!full_command[++(**i)])
	{
		**i = -2;
		node->fd_in = -1;
		ft_error(1, NULL);
		return (node);
	}
	node->fd_in = get_here_doc(node->mini, full_command[(*(*i))],
			"minishell: warning: here-document delimited by end-of-file");
	if (node->fd_in == -1)
	{
		**i = -2;
		node->fd_in = -1;
	}
	node->is_heredoc = 1;
	return (node);
}

t_cmd	*set_redir(t_cmd *node, char *input, char **full_command, int *i)
{
	if (input[0])
	{
		if (input[0] == '>' && input[1] == '>')
			node = handle_redirection(node, full_command, &i, 3); // Append
		else if (input[0] == '>')
			node = handle_redirection(node, full_command, &i, 2); // Truncate
		else if (input[0] == '<' && input[1] == '<')
			node = get_redir_heredoc(node, full_command, &i); // Heredoc
		else if (input[0] == '<')
			node = handle_redirection(node, full_command, &i, 1); // Input
		else if (input[0] != '|')
			node->full_command = ft_add_row_2d_array(node->full_command, input, 0);
	}
	return (node);
}
