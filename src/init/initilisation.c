/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initilisation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:18:28 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 17:33:31 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_basic_env(char **envp)
{
	char	cwd[PATH_MAX];

	g_mini->envp = copy_env(envp);
	if (!g_mini->envp)
	{
		perror("Failed to initialize environment variables");
		exit(EXIT_FAILURE);
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		g_mini->envp = ft_setenv("PWD", cwd, g_mini->envp, 1);
		if (!g_mini->envp)
		{
			perror("Failed to set PWD environment variable");
			exit(EXIT_FAILURE);
		}
	}
	g_mini->envp = ft_setenv("SHELL", "jackoshell", g_mini->envp, 1);
}

static void	set_shell_level(void)
{
	char	*shlvl_str;
	int		shlvl;
	char	shlvl_value[12];

	shlvl_str = ft_getenv("SHLVL", g_mini->envp, strlen("SHLVL"));
	if (shlvl_str)
		shlvl = atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	snprintf(shlvl_value, sizeof(shlvl_value), "%d", shlvl);
	g_mini->envp = ft_setenv("SHLVL", shlvl_value, g_mini->envp, 1);
}

void	initialize_envp(char **envp)
{
	initialize_basic_env(envp);
	set_shell_level();
}

t_cmd	*init_cmd(void)
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
	node->mini = g_mini;
	return (node);
}

void	init_mini(t_mini *mini)
{
	mini->node = NULL;
	mini->current_dir = NULL;
	mini->exit_status = 0;
	mini->signals.sigint_received = 0;
	mini->signals.is_executing_command = 0;
}
