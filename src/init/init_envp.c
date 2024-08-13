/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:45:34 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 12:48:18 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_and_copy_envp(char **envp)
{
	g_mini->envp = copy_env(envp);
	if (!g_mini->envp)
	{
		perror("Failed to initialize environment variables");
		exit(EXIT_FAILURE);
	}
}

static void	set_pwd_env_var(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)))
	{
		g_mini->envp = ft_setenv("PWD", cwd, g_mini->envp, 1);
		if (!g_mini->envp)
		{
			perror("Failed to set PWD environment variable");
			exit(EXIT_FAILURE);
		}
	}
}

static void	set_shell_env_var(void)
{
	g_mini->envp = ft_setenv("SHELL", "jackoshell", g_mini->envp, 1);
}

static void	increment_shlvl_env_var(void)
{
	char	*shlvl_str;
	int		shlvl;
	char	shlvl_value[12];

	shlvl_str = ft_getenv("SHLVL", g_mini->envp, strlen("SHLVL"));
	if (shlvl_str)
		shlvl = atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	g_mini->envp = ft_setenv("SHLVL", shlvl_value, g_mini->envp, 1);
}

void	initialize_envp(char **envp)
{
	initialize_and_copy_envp(envp);
	set_pwd_env_var();
	set_shell_env_var();
	increment_shlvl_env_var();
}
