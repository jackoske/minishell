/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:08:23 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/15 13:46:10 by iverniho         ###   ########.fr       */
x/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*handle_append_redir(t_cmd *cmd, char ***input)
{
	int	fd;

	(*input)++;
	if (!**input)
	{
		return (cmd);
	/*	if (access(path, F_OK) == -1)
		{
			ft_error_with_exit(3, path, 127, ": No such file or directory");
			return (0);
		}
		else if (access(path, R_OK) == -1)
		{
			ft_error_with_exit(5, path, 126, ": Permission denied\n");
			return (0);
		}
		return (1);*/
	}
	fd = open(**input, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(ft_strjoin("minishell: ", **input), STDERR_FILENO);
		perror(" ");
		g_mini->exit_status = 1;
		cmd->fd_out = -1;
		return (cmd);
	/*	if (access(path, F_OK) != -1 && access(path, W_OK) == -1)
		{
			ft_error_with_exit(5, path, 126, ": Permission denied\n");
			return (0);
		}
		return (1);*/
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
		g_mini->exit_status = 1;
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
		g_mini->exit_status = 1;
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

int	process_redirections(t_cmd *cmd, char ***tokenized_input)
{
	if (!*tokenized_input || !**tokenized_input)
		return (0);
	if ((*tokenized_input)[0][0] == '>' && (*tokenized_input)[0][1] == '>')
		cmd = handle_append_redir(cmd, tokenized_input);
	else if ((*tokenized_input)[0][0] == '>')
		cmd = handle_output_redir(cmd, tokenized_input);
	else if ((*tokenized_input)[0][0] == '<' && (*tokenized_input)[0][1] == '<')
		cmd = handle_heredoc_redir(cmd, tokenized_input);
	else if ((*tokenized_input)[0][0] == '<')
		cmd = handle_input_redir(cmd, tokenized_input);
	return (cmd->fd_in == -1 || cmd->fd_out == -1);
}
