/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:52:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 12:49:43 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_directory(char *command)
{
	DIR	*dir;

	dir = opendir(command);
	if (dir != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

static int	is_executable(char *command)
{
	if (access(command, F_OK) == -1)
	{
		ft_error_with_exit(3, command, 127, "No such file or directory\n");
		return (0);
	}
	if (access(command, X_OK) == -1)
	{
		if (errno == EACCES)
			ft_error_with_exit(126, command, 126, "Permission denied\n");
		else
			ft_error_with_exit(127, command, 127, strerror(errno));
		return (0);
	}
	return (1);
}

void	*check_to_fork(t_list *commands)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)commands->content;
	if (is_directory(cmd->full_command[0]))
	{
		ft_error_with_exit(4, cmd->full_command[0], 126, "Is a directory\n");
		return (NULL);
	}
	if (is_builtin(cmd))
	{
		execute_builtin(cmd);
		return (NULL);
	}
	cmd->command_path = resolve_command_path(cmd->full_command[0]);
	if (!cmd->command_path || !is_executable(cmd->command_path))
		return (NULL);
	exec_pipes(commands);
	return (NULL);
}
