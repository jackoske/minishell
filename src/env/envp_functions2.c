/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:55:57 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 12:57:25 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_env_var(const char *name, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!strncmp(envp[i], name, strlen(name))
			&& envp[i][strlen(name)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	update_env_var(char **envp, int index, const char *name,
		const char *value)
{
	char	*temp;
	char	*new_envp;

	temp = ft_strjoin(name, "=");
	new_envp = ft_strjoin_free(temp, (char *)value);
	free(envp[index]);
	envp[index] = new_envp;
}

static char	**add_env_var(const char *name, const char *value, char **envp,
		int count)
{
	char	**new_envp_array;
	char	*temp;
	char	*new_envp;
	int		j;

	new_envp_array = ft_calloc(count + 2, sizeof(char *));
	if (!new_envp_array)
		return (NULL);
	j = 0;
	while (j < count)
	{
		new_envp_array[j] = envp[j];
		j++;
	}
	temp = ft_strjoin(name, "=");
	new_envp = ft_strjoin_free(temp, (char *)value);
	new_envp_array[count] = new_envp;
	new_envp_array[count + 1] = NULL;
	free(envp);
	return (new_envp_array);
}

char	**ft_setenv(const char *name, const char *value, char **envp,
		int overwrite)
{
	int	index;
	int	env_count;

	index = find_env_var(name, envp);
	if (index != -1)
	{
		if (overwrite)
			update_env_var(envp, index, name, value);
		return (envp);
	}
	env_count = 0;
	while (envp && envp[env_count])
		env_count++;
	return (add_env_var(name, value, envp, env_count));
}

void	replace_value(char *key, char *value)
{
	int		i;
	char	**temp;
	char	*temp_key;
	char	*new_env;

	i = 0;
	while (g_mini->envp[i])
	{
		temp = ft_split(g_mini->envp[i], '=');
		if (!temp[0])
			return ;
		temp_key = ft_strdup(temp[0]);
		if (ft_strcmp(temp_key, key) == 0)
		{
			new_env = ft_strjoin(key, ft_strjoin("=", value));
			free(g_mini->envp[i]);
			g_mini->envp[i] = ft_strdup(new_env);
			free(temp_key);
			ft_free_2d_array(&temp);
			return ;
		}
		free(temp_key);
		ft_free_2d_array(&temp);
		i++;
	}
}
