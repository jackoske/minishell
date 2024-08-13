/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:17:19 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 12:21:12 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_redir(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			perror("dup2");
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			perror("dup2");
		close(cmd->fd_out);
	}
	if (cmd->fd_out == -1)
	{
		if (close(STDOUT_FILENO) == -1)
			perror("close");
	}
}

static void	execute_command(t_cmd *cmd)
{
	char	*command_path;

	if (is_builtin(cmd))
	{
		execute_builtin(cmd);
		exit(g_mini->exit_status);
	}
	else
	{
		command_path = resolve_command_path(cmd->full_command[0]);
		if (command_path)
		{
			execve(command_path, cmd->full_command, g_mini->envp);
			if (errno == EACCES)
				ft_error_with_exit(126, cmd->full_command[0], 126,
					"Permission denied\n");
			else
				ft_error_with_exit(127, cmd->full_command[0], 127,
					strerror(errno));
			free(command_path);
			exit(126);
		}
	}
}

void	child_process(t_cmd *cmd)
{
	setup_child_signals();
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		exit(EXIT_FAILURE);
	child_redir(cmd);
	execute_command(cmd);
}

void	create_pipes(int num_cmds, int pipes[][2])
{
	int	i;

	i = -1;
	while (++i < num_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_pipes_in_parent(int num_cmds, int pipes[][2])
{
	int	i;

	i = -1;
	while (++i < num_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}
