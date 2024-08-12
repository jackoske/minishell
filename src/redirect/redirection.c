/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:08:23 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/12 09:39:30 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_access(char *path, int mode)
{
	if (mode == 1)
	{
		if (access(path, F_OK) == -1)
		{
			ft_error_with_exit(3, path, 127, ": No such file or directory");
			return (0);
		}
		else if (access(path, R_OK) == -1)
		{
			ft_error_with_exit(5, path, 126, ": Permission denied");
			return (0);
		}
		return (1);
	}
	else if (mode == 2)
	{
		if (access(path, F_OK) != -1 && access(path, W_OK) == -1)
		{
			ft_error_with_exit(5, path, 126, ": Permission denied");
			return (0);
		}
		return (1);
	}
	return (1);
}

static int	open_file_for_reading(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error_with_exit(3, path, 127, ": Unable to open for reading");
	return (fd);
}

static int	open_file_for_writing(char *path, int append)
{
	int fd;

	if (append)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0666);
	else
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0666);

	if (fd == -1)
		ft_error_with_exit(3, path, 127, ": Unable to open for writing");

	return (fd);
}

static int	determine_fd(t_cmd *cmd, char *path)
{
	if (cmd->is_outfile)
		return open_file_for_writing(path, cmd->is_append);
	else
		return open_file_for_reading(path);
}

int	get_fd(int oldfd, t_cmd *cmd, char *path, int mode)
{
	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (!check_access(path, mode))
		return (-1);

	if (cmd)
		return determine_fd(cmd, path);
	else
	{
		if (mode == 1)
			return open_file_for_reading(path);
		else if (mode == 2)
			return open_file_for_writing(path, 0);
		else if (mode == 3)
			return open_file_for_writing(path, 1);
	}

	return (-1);
}

t_mini	*get_file(t_mini *mini, t_list *command, char **args, int *i)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	(*i)++;
	if (args[*i])
	{
		if (cmd->is_outfile)
			cmd->fd_out = get_fd(cmd->fd_out, cmd, args[*i], cmd->is_append ? 3 : 2);
		else
			cmd->fd_in = get_fd(cmd->fd_in, cmd, args[*i], 1);
	}
	if (!args[*i] || (cmd->is_outfile ? cmd->fd_out : cmd->fd_in) == -1)
	{
		*i = -1;
		if ((cmd->is_outfile ? cmd->fd_out : cmd->fd_in) != -1)
			g_mini->exit_status = 2;
		else
			g_mini->exit_status = 1;
	}
	return (mini);
}
