/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 18:06:33 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 17:47:20 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

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
			{
				path[j++] = (*envp)[i++];
			}
			path[j] = '\0';
			return (path);
		}
		envp++;
	}
	return (NULL);
}

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
		env_path = get_env_path(mini->envp, "HOME=", 5);
		if (!env_path)
		{
			// ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
	}
	else if (option == 1)
	{
		env_path = get_env_path(mini->envp, "OLDPWD=", 7);
		if (!env_path)
		{
			// ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
			return (1);
		}
		if (update_oldpwd(mini) != 0)
			return (1);
	}
	ret = chdir(env_path);
	free(env_path);
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
			print_error(args);
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
	g_mini->current_dir = newpwd;
	// printf("Current directory: %s\n", mini->current_dir);
	free(newpwd);
	return (0);
}
