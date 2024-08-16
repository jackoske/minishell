/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:32:44 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/16 15:32:55 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(int num_cmds, int pipes[][2])
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

void	close_pipes_in_parent(int num_cmds, int pipes[][2])
{
	int	i;

	i = -1;
	while (++i < num_cmds - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

void	close_pipes_in_child(int num_cmds, int pipes[][2], int i)
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

void	setup_pipe_redirection(int i, int num_cmds, int pipes[][2])
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
