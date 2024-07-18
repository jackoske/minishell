/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:43:33 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/16 15:29:18 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if a command is a built-in command
int	is_builtin(t_cmd *cmd)
{
	const char	*builtins[] = {"echo", "pwd", "cd", "export", "unset", "env",
			"exit"};
	size_t		num_builtins;

	if (!cmd->full_command[0])
		return (0);
	num_builtins = sizeof(builtins) / sizeof(builtins[0]);
	for (size_t i = 0; i < num_builtins; i++)
	{
		if (ft_strcmp(cmd->full_command[0], builtins[i]) == 0)
			return (1);
	}
	return (0);
}

// Execute built-in commands
void	execute_builtin(t_mini *mini, t_cmd *cmd)
{
	if (ft_strcmp(cmd->full_command[0], "echo") == 0)
		mini_echo(cmd);
	else if (ft_strcmp(cmd->full_command[0], "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(cmd->full_command[0], "cd") == 0)
		mini->exit_status = mini_cd(cmd->full_command, mini);
	else if (ft_strcmp(cmd->full_command[0], "exit") == 0)
		mini_exit(cmd->full_command, mini);
	// else if (ft_strcmp(cmd->full_command[0], "export") == 0)
	// 	mini_export(cmd->full_command, mini);
	// else if (ft_strcmp(cmd->full_command[0], "unset") == 0)
	// 	mini_unset(cmd->full_command, mini);
	// else if (ft_strcmp(cmd->full_command[0], "env") == 0)
	// 	mini_env(mini);
	mini->exit_status = 0;
}
