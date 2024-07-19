/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:52:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/19 14:25:18 by Jskehan          ###   ########.fr       */
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
			printf("Executing command at path: %s\n", command_path);
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

void	*child_process(t_mini *mini, t_list *command)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	setup_child_signals();
	child_redir(command);
	execute_command(mini, cmd);
	return (NULL); // Should never reach here
}

void	exec_fork(t_mini *mini, t_list *command)
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
		child_process(mini, command);
	}
	else
	{
		waitpid(pid, &status, 0);
		cmd = (t_cmd *)command->content;
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		if (WIFEXITED(status))
		{
			mini->exit_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			mini->exit_status = 128 + WTERMSIG(status);
		}
	}
}

void	*check_to_fork(t_mini *mini, t_list *command)
{
	t_cmd	*cmd;
	DIR		*dir = NULL;

	cmd = (t_cmd *)command->content;

	// Check if the command is a built-in
	if (is_builtin(cmd))
	{
		execute_builtin(mini, cmd);
		return ("");
	}

	// Check if the command is a directory
	if (cmd->full_command && (dir = opendir(cmd->full_command[0])) != NULL)
	{
		closedir(dir);
		mini->exit_status = 126; // Command is a directory
		return ("");
	}

	// Resolve the command path
	cmd->command_path = resolve_command_path(cmd->full_command[0], &mini);

	// Check if the command can be executed
	if (cmd->command_path && access(cmd->command_path, X_OK) == 0)
	{
		exec_fork(mini, command);
	}
	else
	{
		mini->exit_status = 127; // Command not found or not executable
	}

	return ("");
}
