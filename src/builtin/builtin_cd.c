/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:06:33 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/12 16:13:22 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_oldpwd(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (1);
	mini->envp = ft_setenv("OLDPWD", cwd, mini->envp, 1);
	free(oldpwd);
	return (0);
}

static int	go_to_path(int option, t_mini *mini)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (option == 0)
	{
		if (update_oldpwd(mini) != 0)
			return (1);
		env_path = ft_getenv("HOME", mini->envp, 4);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = ft_getenv("OLDPWD", mini->envp, 6);
		if (!env_path)
			return (1);
		if (update_oldpwd(mini) != 0)
			return (1);
	}
	ret = chdir(env_path);
	return (ret);
}

// The `cd` built-in command implementation
int	mini_cd(char **args)
{
	int		cd_ret;
	char	*newpwd;

	if (!args[1])
		return (go_to_path(0, g_mini));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, g_mini);
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
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
	{
		perror("getcwd");
		return (1);
	}
	g_mini->envp = ft_setenv("PWD", newpwd, g_mini->envp, 1);
	if (g_mini->current_dir)
		free(g_mini->current_dir);
	g_mini->current_dir = newpwd;

	return (0);
}
