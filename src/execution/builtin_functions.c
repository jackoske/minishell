/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:40:36 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/16 10:41:39 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_cd(char **args, t_mini *mini)
{
	if (args[1] == NULL || chdir(args[1]) != 0)
	{
		perror("minishell");
		return (1);
	}
	mini->current_dir = getcwd(NULL, 0);
	if (!mini->current_dir)
	{
		perror("minishell");
		return (1);
	}
	return (0);
}

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
		ft_putstr_fd(cmd->full_command[i], 1);
		if (cmd->full_command[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
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
