/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:19:22 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 18:01:36 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		close(pipes[i - 1][0]);
	}
	if (i < num_cmds - 1)
	{
		if (dup2(pipes[i][1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(pipes[i][1]);
	}
}

// static void	wait_for_children(int num_cmds)
// {
// 	int	status;
// 	int	last_exit_code;

// 	last_exit_code = 0;
// 	while (--num_cmds >= 0)
// 	{
// 		wait(&status);
// 		if (WIFEXITED(status))
// 			last_exit_code = WEXITSTATUS(status);
// 		else if (WIFSIGNALED(status))
// 			last_exit_code = 128 + WTERMSIG(status);
// 	}
// 	g_mini->exit_status = last_exit_code;
// }

// static void	process_commands_in_pipes(t_list *commands, int num_cmds,
// 		int pipes[][2])
// {
// 	pid_t	pid;
// 	int		i;
// 	t_cmd	*cmd;

// 	i = 0;
// 	while (i < num_cmds)
// 	{
// 		cmd = (t_cmd *)commands->content;
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			setup_pipe_redirection(i, num_cmds, pipes);
// 			close_pipes_in_child(num_cmds, pipes, i);
// 			child_process(cmd);
// 		}
// 		else if (pid < 0)
// 		{
// 			perror("fork");
// 			g_mini->exit_status = 1;
// 		}
// 		commands = commands->next;
// 		i++;
// 	}
// }

// void	exec_pipes(t_list *commands)
// {
// 	int		num_cmds;
// 	int		pipes[128][2];
// 	t_cmd	*cmd;
// 	pid_t	pid;

// 	num_cmds = ft_lstsize(commands);
// 	if (num_cmds < 2)
// 	{
// 		cmd = (t_cmd *)commands->content;
// 		pid = fork();
// 		if (pid == 0)
// 			child_process(cmd);
// 		else
// 			wait_for_children(1);
// 		return ;
// 	}
// 	create_pipes(num_cmds, pipes);
// 	process_commands_in_pipes(commands, num_cmds, pipes);
// 	close_pipes_in_parent(num_cmds, pipes);
// 	wait_for_children(num_cmds);
// }
