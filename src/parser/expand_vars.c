/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:44 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/08 14:54:51 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(char *var)
{
	int		i;
	char	*value;
	int		var_len;

	i = 0;
	value = NULL;
	var_len = ft_strlen(var);
	while ((g_mini->envp[i]))
	{
		if (ft_strncmp(g_mini->envp[i], var, var_len) == 0
			&& g_mini->envp[i][var_len] == '=')
		{
			value = ft_strdup(g_mini->envp[i] + var_len + 1);
			break ;
		}
		i++;
	}
	return (value);
}

char	**expand_tokens(char **tokenizedInput, char *var)
{
	int		len;
	char	**expanded_array;
	int		i;

	len = ft_2d_array_len(tokenizedInput);
	expanded_array = ft_calloc(len + 1, sizeof(char *));
	if (!expanded_array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		expanded_array[i] = copy_or_replace_token(tokenizedInput[i], var);
		i++;
	}
	return (expanded_array);
}

char	**find_env_var_and_replace(char *var, char **tokenizedInput)
{
	char	*trimmed_var;
	char	**expanded_array;

	trimmed_var = remove_double_quotes(var);
	if (!trimmed_var)
		return (NULL);
	expanded_array = expand_tokens(tokenizedInput, trimmed_var);
	free(trimmed_var);
	return (expanded_array);
}

char	**expand_vars(char **tokenizedInput)
{
	char	**temp_token_array;
	char	**last_str;
	int		i;
	char	**replaced;

	temp_token_array = ft_duplicate_2d_array(tokenizedInput);
	if (!temp_token_array)
		return (NULL);
	last_str = ((i = -1), temp_token_array);
	while (temp_token_array[++i])
	{
		if (ft_strchr(temp_token_array[i], '$') != NULL
			&& (temp_token_array[i][1] != '?'
			&& ft_strlen(temp_token_array[i]) == 2))
		{
			replaced = find_env_var_and_replace(temp_token_array[i],
					tokenizedInput);
			if (replaced)
			{
				ft_free_2d_array(&last_str);
				last_str = replaced;
			}
		}
	}
	return (last_str);
}
