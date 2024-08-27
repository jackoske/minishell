/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 15:33:20 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/27 12:04:26 by iverniho         ###   ########.fr       */
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
	return (ft_strdup(command));
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

char	*remove_quotes2(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
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
