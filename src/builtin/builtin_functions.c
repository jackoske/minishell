/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:40:36 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 18:50:05 by Jskehan          ###   ########.fr       */
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
			show_last_command_status(cmd->full_command);
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
// void	mini_exit(char **args, t_mini *mini)
// {
// 	int	exit_status;

// 	if (args[1])
// 		exit_status = ft_atoi(args[1]);
// 	else
// 		exit_status = mini->exit_status;
// 	// For example: free allocated memory, close file descriptors, etc.
// 	exit(exit_status);
// }
int	ft_isdigit_str(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// Handle the `exit` built-in command
void	mini_exit(char **args)
{
	int	exit_status;

	exit_status = g_mini->exit_status;
	if (ft_2d_array_len(args) > 2)
	{
		ft_error1(8, NULL, 1, "too many arguments");
		exit(1);
	}
	else if (args[1] && !ft_isdigit_str(args[1]))
	{
		ft_error1(7, args[1], 2, "numeric argument required");
		exit(2);
	}
	else if (args[1])
		exit_status = ft_atoi(args[1]);
	else
		exit_status = g_mini->exit_status;
	exit(exit_status);
}
