/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:12:47 by iverniho          #+#    #+#             */
/*   Updated: 2024/07/27 17:54:36 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_mini *mini)
{
	int	i;

	i = -1;
	while (mini->envp[++i])
	{
		ft_putstr_fd(mini->envp[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}
//checks if there is anything after '='
int	check_after_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
		{
			if (str[i + 1] == '\0')
			{
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	is_already_exist(char *key, t_mini *mini)
{
	int	i;
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
	while (mini->envp[++i])
	{
		temp = ft_split(mini->envp[i], '=');
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

void	replace_value(char *key, char *value, t_mini *mini)
{
	int	i;
	char	**temp;
	char	*temp_key;
	char	*new_env;

	i = 0;
	while (mini->envp[i])
	{
		temp = ft_split(mini->envp[i], '=');
		if (!temp[0])
			return ;
		temp_key = ft_strdup(temp[0]);
		if (ft_strcmp(temp_key, key) == 0)
		{
			new_env = ft_strjoin(key, ft_strjoin("=", value));
			free(mini->envp[i]);
			mini->envp[i] = ft_strdup(new_env);
			free(temp_key);
			ft_free_2d_array(&temp);
			return ;
		}
		free(temp_key);
		ft_free_2d_array(&temp);
		i++;
	}
}

int	is_special_char_in_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) || (i > 0 && ft_isdigit(str[i])) || str[i] == '_' || str[i] == '=')
			i++;
		else if (str[i] == '=')
			return (0);
		else
		{
			ft_putstr_fd("minishell> export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}

	}
	return (0);
}
//does actions if there is only key, without any value
int	add_env_if_only_key(char *str, t_mini *mini, int len)
{
	char	*value;
	if (is_already_exist(str, mini))
		return (1);
	if (is_special_char_in_env(str))
		return (1);
	value =	ft_strdup(str);
	value[ft_strlen(str)] = '=';
	value[ft_strlen(str) + 1] = '\0';
	mini->envp[len] = ft_strdup(value);
	mini->envp[len + 1] = NULL;
	return (1);
}


void	mini_export(char **args, t_mini *mini)
{
	char	*key;
	char	*value;
	char	**temp;
	int		len;
	char	*new_env;
	char	**new_envp_array;
	int		i;

	i = -1;
	len = ft_2d_array_len(mini->envp);
	if (ft_2d_array_len(args) < 2)
		return ;
	if ((ft_strchr(*(args + 1), '=') == NULL) || (!check_after_equal(*(args + 1))))
	{
		if (add_env_if_only_key(*(args + 1), mini, len))
			return ;
	}
	value = NULL;
	temp = ft_split(*(args + 1), '=');
	key = ft_strdup(temp[0]);
	value = ft_strdup(temp[1]);
	if (is_already_exist(key, mini))
		return (replace_value(key, value, mini));
	ft_free_2d_array(&temp);
	new_env = ft_strjoin(key, ft_strjoin("=", value));
	new_envp_array = ft_calloc(len + 1, sizeof(char *));
	if (!new_envp_array)
		return ;
	while (mini->envp[++i])
		new_envp_array[i] = ft_strdup(mini->envp[i]);
	new_envp_array[i] = ft_strdup(new_env);
	new_envp_array[i + 1] = NULL;
	mini->envp = new_envp_array;
}

