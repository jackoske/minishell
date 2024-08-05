/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:12:47 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/05 21:26:29 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(void)
{
	int	i;

	i = -1;
	while (g_mini->envp[++i])
	{
		ft_putstr_fd(g_mini->envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

int	is_already_exist(char *key)
{
	int		i;
	char	**temp;
	char	*temp_key;
	char	*key_to_compare;

	i = -1;
	key_to_compare = key;
	if (ft_strchr(key_to_compare, '='))
	{
		temp = ft_split(key_to_compare, '=');
		key_to_compare = ft_strdup(temp[0]);
		ft_free_2d_array(&temp);
	}
	while (g_mini->envp[++i])
	{
		temp = ft_split(g_mini->envp[i], '=');
		if (!temp[0])
			return (1);
		temp_key = ft_strdup(temp[0]);
		if (ft_strcmp(temp_key, key_to_compare) == 0)
			return (free(temp_key), ft_free_2d_array(&temp), 1);
		free(temp_key);
		ft_free_2d_array(&temp);
	}
	return (0);
}

void	copy_envp(t_mini *mini, char ***new_envp_array, char *new_env)
{
	int	i;

	i = -1;
	while (mini->envp[++i])
		(*new_envp_array)[i] = ft_strdup(mini->envp[i]);
	(*new_envp_array)[i] = ft_strdup(new_env);
	(*new_envp_array)[i + 1] = NULL;
	ft_free_2d_array(&mini->envp);
	mini->envp = *new_envp_array;
}

void	export_with_no_args(void)
{
	int	i;

	i = -1;
	while (g_mini->envp[++i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(g_mini->envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	mini_export(char **args)
{
	char	*key;
	char	*value;
	char	**temp;
	char	*new_env;
	char	**new_envp_array;

	if (ft_2d_array_len(args) < 2)
		return (export_with_no_args());
	if (is_special_char_in_env(*(args + 1)))
	{
		g_mini->exit_status = 1;
		return ;
	}
	if (ft_strlen(args[1]) == 1 && args[1][0] == '=')
		return (ft_error_with_exit(9, args[1], 1, NOT_VALID_ID));
	if ((!ft_strchr(*(args + 1), '=')) || (!check_after_equal(*(args + 1))))
		if (add_env_key(*(args + 1), ft_2d_array_len(g_mini->envp) + 1))
			return ;
	value = NULL;
	temp = ft_split(*(args + 1), '=');
	key = ft_strdup(temp[0]);
	value = ft_strdup(temp[1]);
	ft_free_2d_array(&temp);
	if (is_already_exist(key))
		return (replace_value(key, value), free(key), free(value));
	new_env = ft_strjoin(key, ft_strjoin("=", value));
	new_envp_array = ft_calloc((ft_2d_array_len(g_mini->envp) + 1) \
		+ 2, sizeof(char *));
	if (!new_envp_array)
		return (free(key), free(value), free(new_env));
	copy_envp(g_mini, &new_envp_array, new_env);
	return (free(key), free(value), free(new_env));
}
