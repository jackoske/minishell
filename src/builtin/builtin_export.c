/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:32:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/23 14:21:27 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_new_key(char **args)
{
	if ((!ft_strchr(*(args + 1), '=')) || (!check_after_equal(*(args + 1))))
	{
		if (add_env_key(*(args + 1), ft_2d_array_len(g_mini->envp) + 1))
			return (1);
	}
	return (0);
}

static int	prepare_key_value(char **args, char **key, char **value)
{
	char	**temp;

	temp = ft_split(*(args + 1), '=');
	*key = ft_strdup(temp[0]);
	*value = ft_strdup(temp[1]);
	ft_free_2d_array(&temp);
	if (!(*key) || !(*value))
		return (1);
	return (0);
}

static void	replace_existing_value(char *key, char *value)
{
	replace_value(key, value);
	free(key);
	free(value);
}

static void	add_new_env_var(char *key, char *value)
{
	char	*new_env;
	char	**new_envp_array;
	char	*temp;

	temp = ft_strjoin("=", value);
	new_env = ft_strjoin(key, temp);
	free(temp);
	new_envp_array = ft_calloc((ft_2d_array_len(g_mini->envp) + 1) + 2,
			sizeof(char *));
	if (!new_envp_array)
	{
		free(key);
		free(value);
		free(new_env);
		return ;
	}
	copy_envp(g_mini, &new_envp_array, new_env);
	free(key);
	free(value);
	free(new_env);
}

void	mini_export(char **args)
{
	char	*key;
	char	*value;

	if (handle_edge_cases(args))
		return ;
	if (handle_new_key(args))
		return ;
	if (prepare_key_value(args, &key, &value))
	{
		free(key);
		free(value);
		return ;
	}
	if (!is_already_exist(key))
		add_new_env_var(key, value);
	else
		replace_existing_value(key, value);
}
