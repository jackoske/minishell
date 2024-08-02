/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:43:33 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/02 17:57:27 by iverniho         ###   ########.fr       */
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

void	show_last_command_status(t_mini *mini, char **str)
{

	if (ft_2d_array_len(str) == 1)
	{
		ft_putstr_fd(ft_itoa(mini->exit_status), STDERR_FILENO);
		ft_putstr_fd(":  command not found\n", STDERR_FILENO);
		return ;
	}
	ft_putnbr_fd(mini->exit_status, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_mini->exit_status = 127;
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
	else if (ft_strcmp(cmd->full_command[0], "$?") == 0)
		show_last_command_status(mini, cmd->full_command);
	else if (ft_strcmp(cmd->full_command[0], "export") == 0)
		mini_export(cmd->full_command, mini);
	else if (ft_strcmp(cmd->full_command[0], "unset") == 0)
		mini_unset(cmd->full_command, mini);
	else if (ft_strcmp(cmd->full_command[0], "env") == 0)
		mini_env(mini);
	mini->exit_status = 0;
}
