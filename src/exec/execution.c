/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:52:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/12 16:32:35 by Jskehan          ###   ########.fr       */
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
			ft_error_with_exit(126, cmd->full_command[0], 126, "Permission denied\n");
			free(command_path);
			exit(126);
		}
		else
			ft_error_with_exit(127, cmd->full_command[0], 127, "command not found\n");
	}
}

static void	child_process(t_cmd *cmd)
{
	setup_child_signals();
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		exit(EXIT_FAILURE);
	child_redir(cmd);
	execute_command(cmd);
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
		if ((pid = fork()) == 0)
		{
			setup_pipe_redirection(i, num_cmds, pipes);
			close_pipes_in_child(num_cmds, pipes, i);
			child_process(cmd);
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


	cmd = (t_cmd *)commands->content;
	if ((dir = opendir(cmd->full_command[0])) != NULL)
	{
		closedir(dir);
		ft_error_with_exit(4, cmd->full_command[0], 126, "Is a directory\n");
		return (NULL);
	}
	if (is_builtin(cmd))
	{
		execute_builtin(cmd);
		return (NULL);
	}
	cmd->command_path = resolve_command_path(cmd->full_command[0]);
	if (cmd->command_path && access(cmd->command_path, F_OK) == -1)
	{
		ft_error_with_exit(3, cmd->full_command[0], 127, "No such file or directory\n");
		return (NULL);
	}
	if (cmd->command_path && access(cmd->command_path, X_OK) == 0)
		exec_pipes(commands);
	else
		ft_error_with_exit(4, cmd->full_command[0], 127, "command not found\n");
	return (NULL);
}
