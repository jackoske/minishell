/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:52:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/22 16:57:57 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*child_redir(t_list *command)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			return (mini_perror("DUPERR", NULL, 1));
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			return (mini_perror("DUPERR", NULL, 1));
		close(cmd->fd_out);
	}
	return ("");
}

static void	execute_command(t_mini *mini, t_cmd *cmd)
{
	char	*command_path;

	if (is_builtin(cmd))
	{
		execute_builtin(mini, cmd);
		exit(mini->exit_status);
	}
	else
	{
		printf("Resolving path for command: %s\n", cmd->full_command[0]);
		command_path = resolve_command_path(cmd->full_command[0], &mini);
		if (command_path)
		{
			// printf("Executing command at path: %s\n", command_path);
			execve(command_path, cmd->full_command, mini->envp);
			perror("execve");
			free(command_path);
			exit(EXIT_FAILURE);
		}
		else
		{
			mini_perror(CMD_NOT_FOUND, cmd->full_command[0], 127);
			exit(127);
		}
	}
}

void	child_process(t_mini *mini, t_list *command)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	printf("Executing child command: %s\n", cmd->full_command[0]);
	setup_child_signals();
	child_redir(command);
	execute_command(mini, cmd);
}

void	exec_fork(t_mini *mini, t_list *command, int *prev_pipe_fd, int *next_pipe_fd)
{
	pid_t	pid;
	int		status;
	t_cmd	*cmd;

	pid = fork();
	if (pid < 0)
	{
		mini_perror("FORKERR", NULL, 1);
	}
	else if (pid == 0)
	{
		if (prev_pipe_fd)
		{
			if (dup2(prev_pipe_fd[0], STDIN_FILENO) == -1)
				mini_perror("DUPERR", NULL, 1);
			close(prev_pipe_fd[0]);
			close(prev_pipe_fd[1]);
		}
		if (next_pipe_fd)
		{
			if (dup2(next_pipe_fd[1], STDOUT_FILENO) == -1)
				mini_perror("DUPERR", NULL, 1);
			close(next_pipe_fd[0]);
			close(next_pipe_fd[1]);
		}
		child_process(mini, command);
	}
	else
	{
		cmd = (t_cmd *)command->content;
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		if (prev_pipe_fd)
		{
			close(prev_pipe_fd[0]);
			close(prev_pipe_fd[1]);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			mini->exit_status = 128 + WTERMSIG(status);
	}
}

static void	handle_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			mini_perror("DUPERR", NULL, 1);
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			mini_perror("DUPERR", NULL, 1);
		close(cmd->fd_out);
	}
	
}

static void	handle_next_command(t_mini *mini, t_list *command, int *next_pipe_fd)
{
	if (command->next)
	{
		check_to_fork(mini, command->next, next_pipe_fd);
	}
	else
	{
		// Close the next_pipe_fd if it's the last command
		if (next_pipe_fd[0] != -1)
			close(next_pipe_fd[0]);
		if (next_pipe_fd[1] != -1)
			close(next_pipe_fd[1]);
	}
}

static int	is_directory(char *path)
{
	DIR	*dir;

	if ((dir = opendir(path)) != NULL)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

static char	*get_command_path(t_cmd *cmd, t_mini *mini)
{
	char	*command_path;

	command_path = resolve_command_path(cmd->full_command[0], &mini);
	if (command_path && access(command_path, X_OK) == 0)
		return (command_path);
	return (NULL);
}

void	*check_to_fork(t_mini *mini, t_list *command, int *prev_pipe_fd)
{
	t_cmd	*cmd;
	int		next_pipe_fd[2] = {-1, -1};

	cmd = (t_cmd *)command->content;
	if (cmd->full_command == NULL || cmd->full_command[0] == NULL)
	{
		handle_redirections(cmd);
		return ("");
	}
	if (is_builtin(cmd))
	{
		execute_builtin(mini, cmd);
		return ("");
	}
	if (is_directory(cmd->full_command[0]))
	{
		mini->exit_status = 126;
		return ("");
	}
	cmd->command_path = get_command_path(cmd, mini);
	if (cmd->command_path)
	{
		if (command->next && pipe(next_pipe_fd) == -1)
		{
			mini_perror("PIPEERR", NULL, 1);
			return ("");
		}
		exec_fork(mini, command, prev_pipe_fd, command->next ? next_pipe_fd : NULL);
	}
	else
		mini->exit_status = 127; 
	if (prev_pipe_fd)
	{
		close(prev_pipe_fd[0]);
		close(prev_pipe_fd[1]);
	}
	handle_next_command(mini, command, next_pipe_fd);
	return ("");
}
