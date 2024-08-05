/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:52:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 17:31:51 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_redir(t_cmd *cmd)
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
		// printf("fdout = -1\n");
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
			perror("execve");
			free(command_path);
			exit(EXIT_FAILURE);
		}
		else
		{
			// mini_perror(CMD_NOT_FOUND, cmd->full_command[0], 127);
			ft_error1(4, cmd->full_command[0], 127, cmd->full_command[0]);
			exit(127);
		}
	}
}

static void	child_process(t_cmd *cmd)
{
	setup_child_signals();
	child_redir(cmd);
	execute_command(cmd);
}

static void	create_pipes(int num_cmds, int pipes[][2])
{
	for (int i = 0; i < num_cmds - 1; i++)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

static void	close_pipes_in_parent(int num_cmds, int pipes[][2])
{
	for (int i = 0; i < num_cmds - 1; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

static void	close_pipes_in_child(int num_cmds, int pipes[][2], int i)
{
	for (int j = 0; j < num_cmds - 1; j++)
	{
		if (j != i - 1)
			close(pipes[j][0]);
		if (j != i)
			close(pipes[j][1]);
	}
}

static void	setup_pipe_redirection(int i, int num_cmds, int pipes[][2])
{
	if (i > 0)
	{
		if (dup2(pipes[i - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
	if (i < num_cmds - 1)
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
	}
}

static void	wait_for_children(int num_cmds)
{
	int	status;

	for (int k = 0; k < num_cmds; k++)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			// mini->exit_status = WEXITSTATUS(status);
			g_mini->exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			// mini->exit_status = 128 + WTERMSIG(status);
			// g_mini->exit_status = 128 + WTERMSIG(status);
			g_mini->exit_status = 1;

		}
	}
}

void	exec_pipes(t_list *commands)
{
	int		num_cmds;
	int		pipes[128][2]; // Define a maximum number of pipes
	pid_t	pid;
	int		i;
	t_cmd	*cmd;

	num_cmds = ft_lstsize(commands);
	i = 0;
	create_pipes(num_cmds, pipes);
	while (i < num_cmds)
	{
		cmd = (t_cmd *)commands->content;
		if ((pid = fork()) == 0)
		{
			setup_pipe_redirection(i, num_cmds, pipes);
			close_pipes_in_child(num_cmds, pipes, i);
			child_process(cmd);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		commands = commands->next;
		i++;
	}
	close_pipes_in_parent(num_cmds, pipes);
	wait_for_children(num_cmds);
}


void	*check_to_fork(t_list *commands)
{
	t_cmd	*cmd;
	DIR		*dir;

	dir = NULL;
	cmd = (t_cmd *)commands->content;
	if (is_builtin(cmd))
	{
		execute_builtin(cmd);
		return (NULL);
	}
	if (cmd->full_command && (dir = opendir(cmd->full_command[0])) != NULL)
	{
		closedir(dir);
		g_mini->exit_status = 126; // Command is a directory
		return (NULL);
	}
	if (!cmd->full_command && cmd->is_heredoc == 1)
		return (g_mini->exit_status = 127, NULL);// Command not found
	cmd->command_path = resolve_command_path(cmd->full_command[0]);
	if (cmd->command_path && access(cmd->command_path, X_OK) == 0)
		exec_pipes(commands);
	else
		ft_error1(4, cmd->full_command[0], 127, cmd->full_command[0]);
	return (NULL);
}
