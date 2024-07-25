/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:18:28 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/25 16:03:26 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	initialize_envp(t_mini **mini, char **envp)
{
	char	cwd[PATH_MAX];
	char	*shlvl_str;
	int		shlvl;

	*mini = malloc(sizeof(t_mini));
	if (!*mini)
	{
		perror("Failed to allocate t_mini structure");
		exit(EXIT_FAILURE);
	}
	(*mini)->envp = copy_env(envp);
	if (!(*mini)->envp)
	{
		// Handle memory allocation failure
		perror("Failed to initialize environment variables");
		exit(EXIT_FAILURE);
	}
	// Set any additional required environment variables
	if (getcwd(cwd, sizeof(cwd)))
	{
		(*mini)->envp = ft_setenv("PWD", cwd, (*mini)->envp, 1);
		if (!(*mini)->envp)
		{
			perror("Failed to set PWD environment variable");
			exit(EXIT_FAILURE);
		}
	}
	(*mini)->envp = ft_setenv("SHELL", "jackoshell", (*mini)->envp, 1);

	// Handle SHLVL
	shlvl_str = ft_getenv("SHLVL", (*mini)->envp, strlen("SHLVL"));
	if (shlvl_str)
	{
		shlvl = atoi(shlvl_str) + 1;
	}
	else
	{
		shlvl = 1;
	}
	char shlvl_value[12];
	snprintf(shlvl_value, sizeof(shlvl_value), "%d", shlvl);
	(*mini)->envp = ft_setenv("SHLVL", shlvl_value, (*mini)->envp, 1);
}

t_cmd	*init_cmd(t_mini *mini)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->full_command = NULL;
	node->command_path = NULL;
	node->fd_in = 0;
	node->fd_out = 1;
	node->is_heredoc = 0;
	node->is_append = 0;
	node->mini = mini;
	return (node);
}