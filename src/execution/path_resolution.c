/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:23:12 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/18 19:01:24 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*resolve_command_path(char *command, t_mini **mini)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;
	int		i;

	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			return (strdup(command));
		return (NULL);
	}
	path_env = find_var("PATH", mini);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (!cmd_path)
		{
			ft_free_2d_array(&paths);
			return (NULL);
		}
		cmd_path = ft_strjoin_free(cmd_path, command);
		if (!cmd_path)
		{
			ft_free_2d_array(&paths);
			return (NULL);
		}
		if (access(cmd_path, X_OK) == 0)
		{
			printf("Command path found: %s\n", cmd_path); // Debug print
			ft_free_2d_array(&paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_free_2d_array(&paths);
	printf("Command path not found for: %s\n", command); // Debug print
	return (NULL);
}
