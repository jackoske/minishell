/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:40:36 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 17:44:53 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_error_with_exit(NULL, 1, "too many arguments");
		exit(1);
	}
	else if (args[1] && !ft_isdigit_str(args[1]))
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
