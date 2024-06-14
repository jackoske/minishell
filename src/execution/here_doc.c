/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 14:19:34 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/14 17:04:32 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_line_and_append(char *str)
{
	char	*line;
	char	*temp;

	line = readline("> ");
	temp = str;
	str = ft_strjoin(str, line);
	str = ft_strjoin(str, "\n");
	free(temp);
	free(line);
	return (str);
}

static int	line_matches_limit(char *str, char *limit)
{
	size_t	len;

	len = ft_strlen(str) - 1;
	return (str && ft_strncmp(str, limit, len) == 0 && ft_strlen(limit) == len);
}

static char	*read_string_until_limit(t_mini *mini, char *warn)
{
	char	*str;
	char	*limit = NULL;

	str = NULL;
	while (mini->exit_status != 130)
	{
		str = read_line_and_append(str);
		if (!str)
		{
			printf("%s (wanted `%s\')\n", warn, limit);
			break ;
		}
		if (line_matches_limit(str, limit))
			break ;
	}
	return (str);
}

int	get_here_doc(t_mini *mini, char *warn)
{
	int		fd[2];
	char	*str;

	mini->exit_status = 0;
	if (pipe(fd) == -1)
	{
		mini_perror("PIPERR", NULL, 1);
		return (-1);
	}
	str = read_string_until_limit(mini, warn);
	ft_putstr_fd(str, fd[WRITE_END]);
	free(str);
	close(fd[WRITE_END]);
	if (mini->exit_status == 130)
	{
		close(fd[READ_END]);
		return (-1);
	}
	return (fd[READ_END]);
}
