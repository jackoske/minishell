/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:52:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/22 19:06:26 by Jskehan          ###   ########.fr       */
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

void execute_command(t_cmd *cmd)
{
    // Print the command for debugging
    for (int i = 0; cmd->full_command[i] != NULL; i++)
    {
        printf("Arg[%d]: %s\n", i, cmd->full_command[i]);
    }

    if (cmd->fd_in != -1)
    {
        printf("Redirecting input from fd: %d\n", cmd->fd_in);
        if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(cmd->fd_in);
    }

    if (cmd->fd_out != -1)
    {
        printf("Redirecting output to fd: %d\n", cmd->fd_out);
        if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(cmd->fd_out);
    }

    execvp(cmd->full_command[0], cmd->full_command);
    perror("execvp");
    exit(EXIT_FAILURE);
}


void	child_process(t_list *command)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)command->content;
	printf("Executing child command: %s\n", cmd->full_command[0]);
	setup_child_signals();
	child_redir(command);
	execute_command(cmd);
}
void	exec_fork(t_mini *mini, t_list *command, int *prev_pipe_fd, int *next_pipe_fd)
{
	pid_t	pid;
	int		status;
	t_cmd	*cmd = (t_cmd *)command->content;

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
		child_process(command);
	}
	else
	{
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

// Function to handle redirections
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

// Function to handle the next command in the pipeline
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

// Function to check if the command is a directory
static int	is_directory(char *path)
{
	DIR	*dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	return (0);
}

// Function to get the command path
static char	*get_command_path(t_cmd *cmd, t_mini *mini)
{
	char	*command_path = resolve_command_path(cmd->full_command[0], &mini);
	if (command_path && access(command_path, X_OK) == 0)
		return (command_path);
	return (NULL);
}

// Function to check if the command needs to fork and execute
void	*check_to_fork(t_mini *mini, t_list *command, int *prev_pipe_fd)
{
	t_cmd	*cmd = (t_cmd *)command->content;
	int		next_pipe_fd[2] = {-1, -1};

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
	{
		mini->exit_status = 127;
	}
	if (prev_pipe_fd)
	{
		close(prev_pipe_fd[0]);
		close(prev_pipe_fd[1]);
	}
	handle_next_command(mini, command, next_pipe_fd);
	return ("");
}
