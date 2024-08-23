/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:47:19 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/23 14:20:56 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_special_in_key(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (is_special_char_export(str[i]))
			return (g_mini->exit_status = 1, 1);
		if (str[i] == '=')
			return (0);
	}
	return (0);
}

int	check_after_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i++] != '\0')
	{
		if (str[i] == '=')
		{
			if (str[i + 1] == '\0')
				return (0);
		}
	}
	return (1);
}

// does actions if there is only key, without any value
int	add_env_key(char *str, int len)
{
	char	*value;
	char	**new_envp_array;
	int		i;
	char	*original_value;

	value = ((i = -1), NULL);
	if (is_already_exist(str))
		return (1);
	if (is_special_char_in_env(str))
		return (1);
	value = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	original_value = value;
	while (*str)
		*value++ = *str++;
	*value = '=';
	value++;
	*value = '\0';
	new_envp_array = ft_calloc(len + 2, sizeof(char *));
	while (g_mini->envp[++i])
		new_envp_array[i] = ft_strdup(g_mini->envp[i]);
	new_envp_array[i] = ft_strdup(original_value);
	new_envp_array[i + 1] = NULL;
	ft_free_2d_array(&(g_mini->envp));
	g_mini->envp = new_envp_array;
	return (free(original_value), 1);
}

int	is_special_char_in_env(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (((ft_isalpha(str[i]) || (i > 0 && ft_isdigit(str[i]))
					|| str[i] == '_' || str[i] == '='))
			&& (!is_special_char_export(str[i])))
			i++;
		else if (str[i] == '=')
			return (0);
		else
		{
			ft_putstr_fd("minishell> export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_mini->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

void	replace_value(char *key, char *value)
{
	int		i;
	char	**temp;
	char	*temp_key;
	char	*new_env;
	char	*temp_value;

	i = -1;
	while (g_mini->envp[++i])
	{
		temp = ft_split(g_mini->envp[i], '=');
		if (!temp[0])
			return ;
		temp_key = temp[0];
		if (ft_strcmp(temp_key, key) == 0)
		{
			temp_value = ft_strjoin("=", value);
			new_env = ft_strjoin(key, temp_value);
			free(temp_value);
			free(g_mini->envp[i]);
			g_mini->envp[i] = ft_strdup(new_env);
			ft_free_2d_array(&temp);
			return (free(new_env));
		}
		ft_free_2d_array(&temp);
	}
}
