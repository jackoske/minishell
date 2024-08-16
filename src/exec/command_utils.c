/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:33:04 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/16 16:41:50 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_command(t_cmd *cmd)
{
	char	*command_path;

	command_path = resolve_command_path(cmd->full_command[0]);
	if (command_path)
	{
		execve(command_path, cmd->full_command, g_mini->envp);
		perror("execve");
		free(command_path);
		g_mini->exit_status = 126;
	}
	else
		g_mini->exit_status = 127;
	// printf("minishell: %s: %s\n", cmd->full_command[0], strerror(errno));
}

void handle_fd_redirection(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(cmd->fd_out);
	}
}
