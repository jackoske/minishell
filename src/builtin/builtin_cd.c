/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:06:33 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 14:42:50 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_oldpwd(t_mini *mini)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	mini->envp = ft_setenv("OLDPWD", cwd, mini->envp, 1);
	return (0);
}

static int	change_dir_to_env_path(const char *env_var, t_mini *mini)
{
	char	*env_path;
	int		ret;

	env_path = ft_getenv(env_var, mini->envp, strlen(env_var));
	if (!env_path)
		return (1);
	if (update_oldpwd(mini) != 0)
		return (1);
	ret = chdir(env_path);
	return (ret);
}

static int	set_newpwd(t_mini *mini)
{
	char	*newpwd;

	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("getcwd");
		return (1);
	}
	mini->envp = ft_setenv("PWD", newpwd, mini->envp, 1);
	if (mini->current_dir)
		free(mini->current_dir);
	mini->current_dir = newpwd;
	return (0);
}

// The `cd` built-in command implementation
int	mini_cd(char **args)
{
	int	cd_ret;

	if (!args[1])
		return (change_dir_to_env_path("HOME", g_mini));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = change_dir_to_env_path("OLDPWD", g_mini);
	else
	{
		if (update_oldpwd(g_mini) != 0)
			return (1);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
		{
			perror("minishell: cd");
			return (1);
		}
	}
	if (set_newpwd(g_mini) != 0)
		return (1);
	return (0);
}
