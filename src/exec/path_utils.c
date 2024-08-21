/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:33:20 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 17:33:59 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_direct_command(char *command)
{
	if (access(command, F_OK) == -1)
		return (ft_error_with_exit(command, 127, "No such file or directory\n"),
			NULL);
	if (access(command, X_OK) == -1)
		return (ft_error_with_exit(command, 126, "Permission denied\n"), NULL);
	return (strdup(command));
}

char	*try_paths(char **paths, char *command)
{
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		if (!cmd_path)
			return (NULL);
		cmd_path = ft_strjoin_free(cmd_path, command);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

char	*resolve_command_path(char *command)
{
	char	*path_env;
	char	**paths;
	char	*cmd_path;

	if (command[0] == '/' || command[0] == '.')
		return (check_direct_command(command));
	path_env = find_var("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (!paths)
		return (NULL);
	cmd_path = try_paths(paths, command);
	ft_free_2d_array(&paths);
	if (!cmd_path)
		ft_error_with_exit(command, 127, "command not found\n");
	return (cmd_path);
}
