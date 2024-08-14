/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:28:43 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/14 10:45:53 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exit(int exit_code, char *arg, const char *message)
{
	char	*quoted_arg;

	if (message)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		if (arg)
		{
			quoted_arg = ft_quote_string(arg);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(quoted_arg, STDERR_FILENO);
			free(quoted_arg);
		}
	}
	g_mini->exit_status = exit_code;
}

static void	handle_message(int exit_code, const char *message)
{
	if (message)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(message, STDERR_FILENO);
	}
	g_mini->exit_status = exit_code;
}

void	ft_error(int error_code, char *arg)
{
	if (error_code == 1)
		handle_message(1, NEWLINE_ERR);
	else if (error_code == 2)
		handle_message(2, SYNTAX_ERR);
	else if (error_code == 3)
		handle_exit(3, arg, NO_FILE_ERR);
	else if (error_code == 4)
		handle_exit(4, arg, CMD_NOT_FOUND);
	else if (error_code == 5)
		handle_message(5, PERM_ERR);
	else if (error_code == 6)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(ft_strjoin(SYNTAX_ERR, ft_quote_string(arg)),
			STDERR_FILENO);
		g_mini->exit_status = 2;
	}
	else if (error_code == 7)
		handle_exit(7, arg, NUM_REQ);
	else
		handle_exit(error_code, arg, NULL);
}

void	ft_error_with_exit(int error_code, char *arg, int exit_code,
		char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	else
	{
		if (error_code == 1)
			ft_putstr_fd(NEWLINE_ERR, STDERR_FILENO);
		else if (error_code == 2)
			ft_putstr_fd(SYNTAX_ERR, STDERR_FILENO);
		else if (error_code == 3)
			ft_putstr_fd(NO_FILE_ERR, STDERR_FILENO);
		else if (error_code == 4)
			ft_putstr_fd(CMD_NOT_FOUND, STDERR_FILENO);
		else if (error_code == 5)
			ft_putstr_fd(PERM_ERR, STDERR_FILENO);
		else if (error_code == 7)
			ft_putstr_fd(NUM_REQ, STDERR_FILENO);
	}
	g_mini->exit_status = exit_code;
}
