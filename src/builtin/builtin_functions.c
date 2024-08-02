/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:40:36 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/02 17:33:05 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Implementation of echo command with '-n' option
void	mini_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->full_command[i] && ft_strcmp(cmd->full_command[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->full_command[i])
	{
		if (ft_strcmp(cmd->full_command[i], "$?") == 0)
		{
			show_last_command_status(cmd->mini, cmd->full_command);
			return ;
		}
		else
		{
			ft_putstr_fd(cmd->full_command[i], 1);
			if (cmd->full_command[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
	if (newline)
		ft_putstr_fd("\n", 1);
}

// Implementation of pwd command
void	mini_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		free(pwd);
	}
	else
	{
		perror("getcwd");
	}
}
// Handle the `exit` built-in command
void	mini_exit(char **args, t_mini *mini)
{
	int	exit_status;

	if (args[1])
		exit_status = ft_atoi(args[1]);
	else
		exit_status = mini->exit_status;
	// For example: free allocated memory, close file descriptors, etc.
	exit(exit_status);
}
