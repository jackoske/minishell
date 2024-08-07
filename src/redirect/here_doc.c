/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:19:34 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 21:26:29 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_string_until_limit(const char *limit, const char *warn)
{
	char	*str;
	char	*temp;
	char	*line;

	str = NULL;
	while (g_mini->exit_status != 130)
	{
		line = readline("> ");
		if (!line)
		{
			printf("%s (wanted `%s`)\n", warn, limit);
			break ;
		}
		if (strcmp(line, limit) == 0)
		{
			free(line);
			break ;
		}
		temp = str;
		str = ft_strjoin(str, line);
		str = ft_strjoin(str, "\n");
		free(temp);
		free(line);
	}
	return (str);
}

int	get_here_doc(const char *limit, const char *warn)
{
	int		fd[2];
	char	*str;

	g_mini->exit_status = 0;
	if (pipe(fd) == -1)
	{
		// mini_perror("PIPERR", NULL, 1);
		ft_error_with_exit(4, NULL, 1, "pipe");
		return (-1);
	}
	str = read_string_until_limit(limit, warn);
	if (str)
		ft_putstr_fd(str, fd[WRITE_END]);
	free(str);
	close(fd[WRITE_END]);
	if (g_mini->exit_status == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
