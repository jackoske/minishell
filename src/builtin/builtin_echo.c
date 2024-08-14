/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:40:36 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/14 10:23:54 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_newline_option(char **full_command, int *i)
{
	if (full_command[*i] && ft_strcmp(full_command[*i], "-n") == 0)
	{
		(*i)++;
		return (0);
	}
	return (1);
}

static int	handle_special_case(char *arg, char **full_command)
{
	if (ft_strcmp(arg, "$?") == 0)
	{
		show_last_command_status(full_command);
		return (1);
	}
	return (0);
}

static void	print_command_arguments(char **full_command, int start_index,
		int fd_out)
{
	int	i;

	i = start_index;
	while (full_command[i])
	{
		if (handle_special_case(full_command[i], full_command))
			return ;
		ft_putstr_fd(full_command[i], fd_out);
		if (full_command[i + 1])
			ft_putstr_fd(" ", fd_out);
		i++;
	}
}

void	mini_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = check_newline_option(cmd->full_command, &i);
	print_command_arguments(cmd->full_command, i, cmd->fd_out);
	if (newline)
		ft_putstr_fd("\n", cmd->fd_out);
}
