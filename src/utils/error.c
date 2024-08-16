/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:28:43 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/16 14:50:06 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_error_with_exit(int error_code, char *arg, int exit_code,
		char *message)
{
	(void)error_code;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	g_mini->exit_status = exit_code;
}
