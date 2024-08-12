/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:06:08 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/12 12:10:56 by Jskehan          ###   ########.fr       */
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

static void	handle_message(int exit_code, char *arg __attribute__((unused)),
		const char *message)
{
	if (message)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd(message, STDERR_FILENO);
	}
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
	size_t	i;

	i = -1;
	while (++i < sizeof(g_error_table) / sizeof(g_error_table[0]))
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
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(ft_strjoin(SYNTAX_ERR, ft_quote_string(arg)),
			STDERR_FILENO);
		g_mini->exit_status = 2;
	}
	else
	{
		error_info->action(EXIT_SUCCESS, arg, error_info->message);
		if (error_info->action == handle_exit)
			g_mini->exit_status = error_code;
	}
}

void	ft_error_with_exit(int error_code, char *arg, int exit_code,
		char *message)
{
	const t_error_info	*error_info;

	error_info = find_error_info(error_code);
	if (!error_info)
		return ;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	else if (error_info->message)
		ft_putstr_fd(error_info->message, STDERR_FILENO);
	// ft_putstr_fd("\n", STDERR_FILENO); can delete I think
	g_mini->exit_status = exit_code;
}
