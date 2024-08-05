/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 14:06:08 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 21:26:30 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*quote_string(const char *str)
{
	char *quoted_str;
	int i;
	int j;

	quoted_str = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	if (!quoted_str)
		return (NULL);
	i = 0;
	j = 0;
	quoted_str[i++] = '`';
	while (str[j])
		quoted_str[i++] = str[j++];
	quoted_str[i] = '\'';
	return (quoted_str);
}

void	ft_error(int error_code, char *arg)
{
	if (error_code == 1)
		ft_putendl_fd(NEWLINE_ERR, 2);
	else if (error_code == 2)
		ft_putendl_fd(SYNTAX_ERR, 2);
	else if (error_code == 3)
		ft_putendl_fd(NO_FILE_ERR, 2);
	else if (error_code == 4)
		ft_putendl_fd(CMD_NOT_FOUND, 2);
	else if (error_code == 5)
		ft_putendl_fd(PERM_ERR, 2);
	else if (error_code == 6)
		ft_putendl_fd(ft_strjoin(SYNTAX_ERR, quote_string(arg)), 2);
}

void	ft_error_with_exit(int error_code, char *arg, int exit_code,
		char *message)
{
	if (error_code == 1)
		ft_putendl_fd(NEWLINE_ERR, 2);
	else if (error_code == 2)
		ft_putendl_fd(SYNTAX_ERR, 2);
	else if (error_code == 3)
	{
		ft_putendl_fd(NO_FILE_ERR, 2);
		g_mini->exit_status = exit_code;
	}
	else if (error_code == 4)
	{
		ft_putstr_fd(message, 2);
		ft_putendl_fd(CMD_NOT_FOUND, 2);
		g_mini->exit_status = exit_code;
	}
	else if (error_code == 5)
		ft_putendl_fd(PERM_ERR, 2);
	else if (error_code == 6)
		ft_putendl_fd(ft_strjoin(SYNTAX_ERR, quote_string(arg)), 2);
	else if (error_code == 7)
	{
		ft_putstr_fd("minishell> exit: ", STDERR_FILENO);
		ft_putendl_fd(NUM_REQ, 2);
		g_mini->exit_status = exit_code;
	}
	else if (error_code == 8)
	{
		ft_putstr_fd("minishell> exit: ", STDERR_FILENO);
		ft_putendl_fd(message, 2);
		g_mini->exit_status = exit_code;
	}
	else if (error_code == 9)
	{
		ft_putstr_fd("minishell> export: ", STDERR_FILENO);
		ft_putendl_fd(ft_strjoin(quote_string(arg), message), 2);
		g_mini->exit_status = exit_code;
	}
}
