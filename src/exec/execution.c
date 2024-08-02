/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:52:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/02 11:21:12 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*child_redir(t_list *command, int *pipe_fd, int in_fd, int out_fd)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
			return (mini_perror("DUPERR", NULL, 1));
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			return (mini_perror("DUPERR", NULL, 1));
		close(out_fd);
	}
	if (pipe_fd)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
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
		command_path = resolve_command_path(cmd->full_command[0], &mini);
		if (command_path)
		{
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

void	child_process(t_mini *mini, t_list *command, int *pipe_fd, int in_fd, int out_fd)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	setup_child_signals();
	child_redir(command, pipe_fd, in_fd, out_fd);
	execute_command(mini, cmd);
}
void	exec_fork(t_mini *mini, t_list *command, int in_fd, int out_fd)
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
		child_process(mini, command, NULL, in_fd, out_fd);
	}
	else
	{
		cmd = (t_cmd *)command->content;
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		waitpid(pid, &status, 0);
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

void execute_pipeline(t_mini *mini, t_list *commands)
{
    int pipe_fd[2];
    int in_fd = STDIN_FILENO;
    int out_fd = STDOUT_FILENO;
    t_list *current = commands;

    while (current)
    {
        t_list *next = current->next;
        t_cmd *cmd = (t_cmd *)current->content;

        if (next)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            out_fd = pipe_fd[1];
        }
        else
        {
            // Check if the last command has output redirection
            if (cmd->fd_out != STDOUT_FILENO)
            {
                out_fd = cmd->fd_out;
            }
            else
            {
                out_fd = STDOUT_FILENO;
            }
        }

        exec_fork(mini, current, in_fd, out_fd);

        if (in_fd != STDIN_FILENO)
            close(in_fd);
        if (out_fd != STDOUT_FILENO)
            close(out_fd);

        in_fd = pipe_fd[0];
        current = next;
    }

    while (wait(NULL) > 0)
        ; // Wait for all child processes to finish
}

void	*check_to_fork(t_mini *mini, t_list *command)
{
	t_cmd	*cmd;
	DIR		*dir = NULL;

	cmd = (t_cmd *)command->content;

	if (is_builtin(cmd))
	{
		execute_builtin(mini, cmd);
		return ("");
	}
	if (cmd->full_command && (dir = opendir(cmd->full_command[0])) != NULL)
	{
		closedir(dir);
		mini->exit_status = 126; // Command is a directory
		return ("");
	}
	if (!cmd->full_command && cmd->is_heredoc == 1)
	{
		mini->exit_status = 127; // Command not found
		return ("");
	}

	cmd->command_path = resolve_command_path(cmd->full_command[0], &mini);
	if (cmd->command_path && access(cmd->command_path, X_OK) == 0)
		exec_fork(mini, command, STDIN_FILENO, STDOUT_FILENO);
	else
		mini->exit_status = 127; // Command not found or not executable
	return ("");
}
