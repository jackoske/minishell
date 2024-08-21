/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:40:36 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 17:44:44 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Handle the `exit` built-in command
void	mini_exit(char **args)
{
	int	exit_status;

	exit_status = g_mini->exit_status;
	if (ft_2d_array_len(args) > 2)
	{
		ft_error_with_exit(NULL, 1, "too many arguments");
		exit(1);
	}
	else if (args[1] && !ft_isstr_digit(args[1]))
	{
		ft_error_with_exit(args[1], 2, "numeric argument required");
		exit(2);
	}
	else if (args[1])
		exit_status = ft_atoi(args[1]);
	else
		exit_status = g_mini->exit_status;
	exit(exit_status);
}
