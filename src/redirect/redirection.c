/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:23:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/20 12:40:06 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*handle_append_redir(t_cmd *cmd, char ***input)
{
	int	fd;

	(*input)++;
	if (!**input)
	{
		cmd->fd_out = -1;
		return (cmd);
	}
	fd = open(**input, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(ft_strjoin("minishell: ", **input), STDERR_FILENO);
		perror(" ");
		cmd->fd_out = -1;
		return (cmd);
	}
	cmd->fd_out = fd;
	(*input)++;
	return (cmd);
}

static t_cmd	*handle_output_redir(t_cmd *cmd, char ***input)
{
	int	fd;

	(*input)++;
	if (!**input)
	{
		cmd->fd_out = -1;
		return (cmd);
	}
	fd = open(**input, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(ft_strjoin("minishell: ", **input), STDERR_FILENO);
		perror(" ");
		cmd->fd_out = -1;
		return (cmd);
	}
	cmd->fd_out = fd;
	(*input)++;
	return (cmd);
}

static t_cmd	*handle_input_redir(t_cmd *cmd, char ***input)
{
	int	fd;

	(*input)++;
	if (!**input)
	{
		cmd->fd_in = -1;
		return (cmd);
	}
	fd = open(**input, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(ft_strjoin("minishell: ", **input), STDERR_FILENO);
		perror(" ");
		cmd->fd_in = -1;
		return (cmd);
	}
	cmd->fd_in = fd;
	(*input)++;
	return (cmd);
}

static t_cmd	*handle_heredoc_redir(t_cmd *cmd, char ***input)
{
	(*input)++;
	if (!**input)
	{
		cmd->fd_in = -1;
		return (cmd);
	}
	cmd->fd_in = get_here_doc(**input);
	if (cmd->fd_in == -1)
	{
		cmd->fd_in = -1;
		return (cmd);
	}
	cmd->is_heredoc = 1;
	(*input)++;
	return (cmd);
}

void	process_redirections(t_cmd *cmd, char ***tokenized_input)
{
	if (!*tokenized_input || !**tokenized_input)
		return ;
	if ((*tokenized_input)[0][0] == '>' && (*tokenized_input)[0][1] == '>')
		cmd = handle_append_redir(cmd, tokenized_input);
	else if ((*tokenized_input)[0][0] == '>')
		cmd = handle_output_redir(cmd, tokenized_input);
	else if ((*tokenized_input)[0][0] == '<' && (*tokenized_input)[0][1] == '<')
		cmd = handle_heredoc_redir(cmd, tokenized_input);
	else if ((*tokenized_input)[0][0] == '<')
		cmd = handle_input_redir(cmd, tokenized_input);
}
