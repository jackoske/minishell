/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:52:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/16 10:52:26 by Jskehan          ###   ########.fr       */
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

void	*child_process(t_mini *mini, t_list *command)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	child_redir(command);
	if (is_builtin(cmd))
	{
		execute_builtin(mini, cmd);
		exit(mini->exit_status);
	}
	if (cmd->command_path)
	{
		execve(cmd->command_path, cmd->full_command, mini->envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	exit(mini->exit_status);
}

void	exec_fork(t_mini *mini, t_list *command)
{
	pid_t	pid;

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
		waitpid(pid, &mini->exit_status, 0);
	}
}

void	*check_to_fork(t_mini *mini, t_list *command)
{
	t_cmd	*cmd;
	DIR		*dir;

	cmd = (t_cmd *)command->content;
	dir = NULL;
	if (cmd->full_command)
		dir = opendir(*cmd->full_command);
	if (cmd->fd_in == -1 || cmd->fd_out == -1)
		return (NULL);
	if ((cmd->command_path && access(cmd->command_path, X_OK) == 0)
		|| is_builtin(cmd))
		exec_fork(mini, command);
	else if (!is_builtin(cmd) && ((cmd->command_path
				&& !access(cmd->command_path, F_OK)) || dir))
		mini->exit_status = 126;
	else if (!is_builtin(cmd) && cmd->full_command)
		mini->exit_status = 127;
	if (dir)
		closedir(dir);
	return ("");
}
