/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:49:43 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 18:09:02 by Jskehan          ###   ########.fr       */
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

char	**ft_setenv(const char *name, const char *value, char **envp,
		int overwrite)
{
	int		i;
	char	*new_envp;
	char	**new_envp_array;
	char	*temp;

	i = 0;
	while (envp && envp[i])
	{
		if (!strncmp(envp[i], name, strlen(name))
			&& envp[i][strlen(name)] == '=')
		{
			if (overwrite)
			{
				temp = ft_strjoin(name, "=");
				new_envp = ft_strjoin_free(temp, (char *)value);
				free(envp[i]);
				envp[i] = new_envp;
			}
			return (envp);
		}
		i++;
	}
	printf("No existing entry found, adding new\n");
	new_envp_array = ft_calloc(i + 2, sizeof(char *));
	if (!new_envp_array)
	{
		printf("Memory allocation for new_envp_array failed\n");
		return (NULL);
	}
	for (int j = 0; j < i; j++)
	{
		new_envp_array[j] = envp[j];
	}
	temp = ft_strjoin(name, "=");
	new_envp = ft_strjoin_free(temp, (char *)value);
	new_envp_array[i] = new_envp;
	new_envp_array[i + 1] = NULL;
	free(envp);
	printf("New environment variable added: %s=%s\n", name, value);
	return (new_envp_array);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**new_envp;

	for (i = 0; envp[i]; i++)
		;
	new_envp = malloc((i + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	for (i = 0; envp[i]; i++)
	{
		new_envp[i] = strdup(envp[i]);
		if (!new_envp[i])
		{
			while (i--)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
	}
	new_envp[i] = NULL;
	return (new_envp);
}
