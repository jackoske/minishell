/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:08:23 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 12:24:13 by Jskehan          ###   ########.fr       */
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
	}
	else if (mode == 2)
	{
		if (access(path, F_OK) != -1 && access(path, W_OK) == -1)
		{
			ft_error_with_exit(5, path, 126, ": Permission denied");
			return (0);
		}
	}
	return (1);
}

static int	open_file_for_reading(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		ft_error_with_exit(3, path, 127, ": Unable to open for reading");
	return (fd);
}

static int	open_file_for_writing(char *path, int append)
{
	int	fd;

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
		return (open_file_for_writing(path, cmd->is_append));
	else
		return (open_file_for_reading(path));
}

int	get_fd(int oldfd, t_cmd *cmd, char *path, int mode)
{
	int	fd;

	if (oldfd > 2)
		close(oldfd);
	if (!path)
		return (-1);
	if (!check_access(path, mode))
		return (-1);
	if (cmd)
		fd = determine_fd(cmd, path);
	else
	{
		if (mode == 1)
			fd = open_file_for_reading(path);
		else if (mode == 2)
			fd = open_file_for_writing(path, 0);
		else if (mode == 3)
			fd = open_file_for_writing(path, 1);
		else
			return (-1);
	}
	if (fd == -1)
		return (-1);
	return (fd);
}
