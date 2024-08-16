/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:23:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/16 17:00:36 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*handle_append_redir(t_cmd *cmd, char **input, int *i)
{
	int	fd;

	fd = open(input[++(*i)], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		cmd->fd_out = -1;
		*i = -2;
		return (cmd);
	}
	cmd->fd_out = fd;
	return (cmd);
}

static t_cmd	*handle_output_redir(t_cmd *cmd, char **input, int *i)
{
	int	fd;

	fd = open(input[++(*i)], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		cmd->fd_out = -1;
		*i = -2;
		return (cmd);
	}
	cmd->fd_out = fd;
	return (cmd);
}

static t_cmd	*handle_input_redir(t_cmd *cmd, char **input, int *i)
{
	int	fd;

	fd = open(input[++(*i)], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		cmd->fd_in = -1;
		*i = -2;
		return (cmd);
	}
	cmd->fd_in = fd;
	return (cmd);
}

static t_cmd	*handle_heredoc_redir(t_cmd *cmd, char **input, int *i)
{
	if (!input[++(*i)])
	{
		cmd->fd_in = -1;
		*i = -2;
		return (cmd);
	}
	cmd->fd_in = get_here_doc(input[(*i)],
			"minishell: warning: here-document delimited by end-of-file");
	if (cmd->fd_in == -1)
	{
		*i = -2;
		cmd->fd_in = -1;
	}
	cmd->is_heredoc = 1;
	return (cmd);
}

void	process_redirections(t_cmd *cmd, char **tokenized_input, int *i)
{
	if (tokenized_input[*i][0] == '>' && tokenized_input[*i][1] == '>')
		cmd = handle_append_redir(cmd, tokenized_input, i);
	else if (tokenized_input[*i][0] == '>')
		cmd = handle_output_redir(cmd, tokenized_input, i);
	else if (tokenized_input[*i][0] == '<' && tokenized_input[*i][1] == '<')
		cmd = handle_heredoc_redir(cmd, tokenized_input, i);
	else if (tokenized_input[*i][0] == '<')
		cmd = handle_input_redir(cmd, tokenized_input, i);
}
