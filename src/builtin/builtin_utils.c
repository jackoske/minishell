/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:43:33 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/12 16:34:19 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if a command is a built-in command
int	is_builtin(t_cmd *cmd)
{
	const char	*builtins[] = {"echo", "pwd", "cd", "export", "unset", "env",
		"exit", "$?"};
	size_t		num_builtins;
	size_t		i;

	i = 0;
	if (!cmd || !cmd->full_command || !cmd->full_command[0])
		return (0);
	num_builtins = sizeof(builtins) / sizeof(builtins[0]);
	while (i < num_builtins)
	{
		if (ft_strcmp(cmd->full_command[0], builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	show_last_command_status(char **str)
{
	char	*exit_status;

	if (ft_2d_array_len(str) == 1)
	{
		g_mini->exit_status = 127;
		exit_status = ft_itoa(g_mini->exit_status);
		ft_putstr_fd(exit_status, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free(exit_status);
		return ;
	}
	ft_putnbr_fd(g_mini->exit_status, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

// Execute built-in commands
void	execute_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->full_command[0], "echo") == 0)
		return (mini_echo(cmd));
	else if (ft_strcmp(cmd->full_command[0], "pwd") == 0)
		mini_pwd();
	else if (ft_strcmp(cmd->full_command[0], "cd") == 0)
		g_mini->exit_status = mini_cd(cmd->full_command);
	else if (ft_strcmp(cmd->full_command[0], "exit") == 0)
		mini_exit(cmd->full_command);
	else if (ft_strcmp(cmd->full_command[0], "$?") == 0)
		show_last_command_status(cmd->full_command);
	else if (ft_strcmp(cmd->full_command[0], "export") == 0)
		return (mini_export(cmd->full_command));
	else if (ft_strcmp(cmd->full_command[0], "unset") == 0)
		mini_unset(cmd->full_command);
	else if (ft_strcmp(cmd->full_command[0], "env") == 0)
		mini_env();
	else
		g_mini->exit_status = 0;
}
