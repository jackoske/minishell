/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:52:13 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 12:17:27 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	handle_child(t_cmd *cmd, int pipes[][2], int i, int num_cmds)
{
	setup_child_signals();
	setup_pipe_redirection(i, num_cmds, pipes);
	handle_fd_redirection(cmd);
	if (is_builtin(cmd))
		execute_builtin(cmd);
	else
		execute_command(cmd);
	exit(g_mini->exit_status);
}

void	exec_pipes(t_list *commands)
{
	int		num_cmds;
	int		pipes[128][2];
	pid_t	pid;
	int		i;
	t_cmd	*cmd;

	num_cmds = ft_lstsize(commands);
	create_pipes(num_cmds, pipes);
	i = 0;
	while (i < num_cmds)
	{
		cmd = (t_cmd *)commands->content;
		if (is_builtin(cmd) && num_cmds == 1)
		{
			execute_builtin(cmd);
			return ;
		}
		if ((pid = fork()) == 0)
		{
			close_pipes_in_child(num_cmds, pipes, i);
			handle_child(cmd, pipes, i, num_cmds);
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
