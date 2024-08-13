/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:49:43 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/13 12:57:06 by Jskehan          ###   ########.fr       */
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
		new_envp[i] = strdup(envp[i]);
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
