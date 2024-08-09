/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:06:08 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/09 17:04:18 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_exit(int exit_code, char *arg, const char *message)
{
	if (message)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		if (arg)
			ft_putendl_fd(ft_strjoin(ft_quote_string(arg), CMD_NOT_FOUND),
				STDERR_FILENO);
		else
			ft_putendl_fd("", STDERR_FILENO);
	}
	g_mini->exit_status = exit_code;
	exit(exit_code);
}

static void	handle_message(int exit_code, char *arg __attribute__((unused)),
		const char *message)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	g_mini->exit_status = exit_code;
}

static t_error_info			g_error_table[] = {
	{1, NEWLINE_ERR, handle_message},
	{2, SYNTAX_ERR, handle_message},
	{3, NO_FILE_ERR, handle_exit},
	{4, CMD_NOT_FOUND, handle_exit},
	{5, PERM_ERR, handle_message},
	{6, NULL, handle_message}, // Special case handled in the function below
	{7, NUM_REQ, handle_exit},
	{8, NULL, handle_exit}, // Custom message will be passed
	{9, NULL, handle_exit}  // Special case handled in the function below
};

static const t_error_info	*find_error_info(int error_code)
{
	size_t i;

	i = -1;
	while ( ++i < sizeof(g_error_table)
		/ sizeof(g_error_table[0]))
	{
		if (g_error_table[i].error_code == error_code)
			return (&g_error_table[i]);
	}
	return (NULL);
}

void	ft_error(int error_code, char *arg)
{
	const t_error_info	*error_info;

	error_info = find_error_info(error_code);
	if (!error_info)
		return ;
	if (error_code == 6)
		ft_putendl_fd(ft_strjoin(SYNTAX_ERR, ft_quote_string(arg)), STDERR_FILENO);
	else
		error_info->action(EXIT_SUCCESS, arg, error_info->message);
}

void	ft_error_with_exit(int error_code, char *arg, int exit_code,
		char *message)
{
	const t_error_info	*error_info;

	error_info = find_error_info(error_code);
	if (!error_info)
		return ;
	if (error_code == 6 || error_code == 9)
	{
		if (error_code == 6)
			ft_putendl_fd(ft_strjoin(SYNTAX_ERR, ft_quote_string(arg)),
				STDERR_FILENO);
		else
			ft_putstr_fd("minishell> export: ", STDERR_FILENO);
		ft_putendl_fd(ft_strjoin(ft_quote_string(arg), message), STDERR_FILENO);
		g_mini->exit_status = exit_code;
		exit(exit_code);
	}
	else
	{
		error_info->action(exit_code, arg,
			message ? message : error_info->message);
	}
}
