/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:44 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/09 13:52:09 by iverniho         ###   ########.fr       */
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

char	**replace_var(char *tempTokenArray, char **tokenizedInput)
{
	char	**expanded_array;
	int		i;
	char	*var_value;

	i = -1;
	expanded_array = ft_calloc(ft_2d_array_len(tokenizedInput) + 1, \
		sizeof(char *));
	if (!expanded_array)
		return (NULL);
	while (tokenizedInput[++i])
	{
		if (ft_strchr(tokenizedInput[i], '$') == NULL)
			expanded_array[i] = ft_strdup(tokenizedInput[i]);
		else
		{
			var_value = find_var(tempTokenArray);
			if (var_value)
				expanded_array[i] = var_value;
			else
				expanded_array[i] = ft_strdup(tokenizedInput[i]);
		}
	}
	free(tempTokenArray);
	return (expanded_array);
}

char	**find_env_var_and_replace(char *var, char **tokenizedInput)
{
	char	*temp_token_array;
	char	*tmp;
	int		j;
	char	**res;

	j = 0;
	temp_token_array = ft_calloc(ft_strlen(var) + 1, sizeof(char));
	if (!temp_token_array)
		return (NULL);
	tmp = remove_double_quotes(var);
	while (*tmp)
		temp_token_array[j++] = *++tmp;
	temp_token_array[j] = '\0';
	res = replace_var(temp_token_array, tokenizedInput);
	if (!res)
		return (free(temp_token_array), NULL);
	return (res);
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
	last_str = temp_token_array;
	i = -1;
	while (temp_token_array[++i])
	{
		if (ft_strchr(temp_token_array[i], '$') != NULL
			&& (temp_token_array[i][1] != '?'
			&& ft_strlen(temp_token_array[i]) != 2))
		{
			replaced = find_env_var_and_replace(temp_token_array[i],
					tokenizedInput);
			if (replaced)
				last_str = manage_replaced(replaced, last_str);
		}
	}
	return (last_str);
}
