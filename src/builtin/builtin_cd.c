/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:06:33 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/14 10:21:18 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_path(char **envp, const char *var, size_t len)
{
	char	*path;
	int		i;
	int		j;
	int		s_alloc;

	while (envp && *envp)
	{
		if (ft_strncmp(*envp, var, len) == 0)
		{
			s_alloc = ft_strlen(*envp) - len;
			if (!(path = malloc(sizeof(char) * (s_alloc + 1))))
				return (NULL);
			i = len;
			j = 0;
			while ((*envp)[i])
				path[j++] = (*envp)[i++];
			path[j] = '\0';
			return (path);
		}
		envp++;
	}
	return (NULL);
}

static int	update_oldpwd(void)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (!(oldpwd = ft_strjoin("OLDPWD=", cwd)))
		return (1);
	g_mini->envp = ft_setenv("OLDPWD", cwd, g_mini->envp, 1);
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
		if (update_oldpwd() != 0)
			return (1);
		env_path = get_env_path(mini->envp, "HOME=", 5);
		if (!env_path)
			return (1);
	}
	else if (option == 1)
	{
		env_path = get_env_path(mini->envp, "OLDPWD=", 7);
		if (!env_path)
			return (1);
		if (update_oldpwd() != 0)
			return (1);
	}
	ret = chdir(env_path);
	free(env_path);
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
		return (go_to_path(0, g_mini));
	if (ft_strcmp(args[1], "-") == 0)
		cd_ret = go_to_path(1, g_mini);
	else
	{
		if (update_oldpwd() != 0)
			return (1);
		cd_ret = chdir(args[1]);
		if (cd_ret < 0)
		{
			perror("minishell: cd");
			return (1);
		}
	}
	if (cd_ret == 0)
	{
		if (set_newpwd(g_mini) != 0)
			return (1);
	}
	return (0);
}
