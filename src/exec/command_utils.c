/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:33:04 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/22 14:38:33 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *command_path)
{
	int		fd;
	char	buf;

	fd = open(command_path, O_RDONLY);
	if (fd != -1)
	{
		if (read(fd, &buf, 1) == -1 && errno == EISDIR)
		{
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}

void	execute_command(t_cmd *cmd)
{
	char	*command_path;

	command_path = resolve_command_path(cmd->full_command[0]);
	if (command_path)
	{
		if (is_directory(command_path))
		{
			fprintf(stderr, "minishell: %s: Is a directory\n", command_path);
			free(command_path);
			g_mini->exit_status = 126;
			return ;
		}
		execve(command_path, cmd->full_command, g_mini->envp);
		ft_putstr_fd("minishell :", STDERR_FILENO);
		perror("");
		free(command_path);
		g_mini->exit_status = 126;
	}
}

void	handle_fd_redirection(t_cmd *cmd)
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
