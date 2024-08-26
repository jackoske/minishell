/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:49:43 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/26 19:19:01 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(const char *name, char **envp, int len)
{
	int	i;
	int	j;

	i = -1;
	while (envp && envp[++i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] == name[j] && name[j])
			j++;
		if (j == len && envp[i][j] == '=')
			return (envp[i] + j + 1);
	}
	return (NULL);
}

static char	*update_existing_envp(char **envp, const char *name,
		const char *value, int overwrite)
{
	int		i;
	char	*new_envp;
	char	*temp;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], name, strlen(name))
			&& envp[i][strlen(name)] == '=')
		{
			if (overwrite)
			{
				temp = ft_strjoin(name, "=");
				new_envp = ft_strjoin_free(temp, (char *)value);
				free(envp[i]);
				envp[i] = new_envp;
			}
			return (envp[i]);
		}
		i++;
	}
	return (NULL);
}

static char	**add_new_envp(char **envp, const char *name, const char *value,
		int count)
{
	char	**new_envp_array;
	char	*new_envp;
	char	*temp;
	int		j;

	j = 0;
	new_envp_array = ft_calloc(count + 2, sizeof(char *));
	if (!new_envp_array)
	{
		printf("Memory allocation for new_envp_array failed\n");
		return (NULL);
	}
	while (j < count)
	{
		new_envp_array[j] = envp[j];
		j++;
	}
	temp = ft_strjoin(name, "=");
	new_envp = ft_strjoin_free(temp, (char *)value);
	new_envp_array[count] = new_envp;
	new_envp_array[count + 1] = NULL;
	return (new_envp_array);
}

char	**ft_setenv(const char *name, const char *value, char **envp,
		int overwrite)
{
	int		i;
	char	*updated_envp;

	i = 0;
	updated_envp = update_existing_envp(envp, name, value, overwrite);
	if (updated_envp)
		return (envp);
	while (envp && envp[i])
		i++;
	return (add_new_envp(envp, name, value, i));
}

char	**copy_env(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i])
		i++;
	new_envp = malloc((i + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i--)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
