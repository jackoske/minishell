/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:52:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/16 11:15:42 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command(t_cmd *cmd)
{
	char	*command_path;

	command_path = resolve_command_path(cmd->full_command[0]);
	if (command_path)
	{
		execve(command_path, cmd->full_command, g_mini->envp);
		perror("execve");
		free(command_path);
		exit(126);
	}
	else
		exit(g_mini->exit_status);
}

static void	create_pipes(int num_cmds, int pipes[][2])
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

static void	close_pipes_in_parent(int num_cmds, int pipes[][2])
{
	int	i;

	i = -1;
	while (++i < num_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

static void	close_pipes_in_child(int num_cmds, int pipes[][2], int i)
{
	int	j;

	j = -1;
	while (++j < num_cmds - 1)
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

	while (--num_cmds >= 0)
	{
		wait(&status);
		if (WIFEXITED(status))
			g_mini->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_mini->exit_status = 1;
	}
}

static void	child_process(t_cmd *cmd, int pipes[][2], int i, int num_cmds)
{
	setup_child_signals();
	setup_pipe_redirection(i, num_cmds, pipes);
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
	if (is_builtin(cmd))
	{
		execute_builtin(cmd);
		exit(g_mini->exit_status);
	}
	else
		execute_command(cmd);
}

void	exec_pipes(t_list *commands)
{
	int		num_cmds;
	int		pipes[128][2];
	pid_t	pid;
	int		i;
	t_cmd	*cmd;

	num_cmds = ft_lstsize(commands);
	i = 0;
	create_pipes(num_cmds, pipes);
	while (i < num_cmds)
	{
		cmd = (t_cmd *)commands->content;
		if (!cmd) // If cmd is NULL, skip execution
		{
			g_mini->exit_status = 1;
			break ;
		}
		if ((pid = fork()) == 0)
		{
			close_pipes_in_child(num_cmds, pipes, i);
			child_process(cmd, pipes, i, num_cmds);
		}
		else if (pid < 0)
		{
			perror("fork");
			g_mini->exit_status = 1;
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

	if (!commands || !(cmd = (t_cmd *)commands->content) || !cmd->full_command || !cmd->full_command[0])
	{
		g_mini->exit_status = 1;
		return (NULL);
	}
	
	if ((dir = opendir(cmd->full_command[0])) != NULL)
	{
		closedir(dir);
		ft_error_with_exit(4, cmd->full_command[0], 126, "Is a directory\n");
		return (NULL);
	}
	cmd->command_path = resolve_command_path(cmd->full_command[0]);
	if (cmd->command_path && access(cmd->command_path, F_OK) == -1)
	{
		ft_error_with_exit(3, cmd->full_command[0], 127,
			"No such file or directory\n");
		return (NULL);
	}
	if (cmd->command_path && access(cmd->command_path, X_OK) == 0)
		exec_pipes(commands);
	else
	{
		ft_error_with_exit(3, cmd->full_command[0], 126,
			"Permission denied\n");
		return (NULL);
	}
	return (NULL);
}
