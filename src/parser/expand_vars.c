/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:44 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/15 13:40:53 by iverniho         ###   ########.fr       */
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
	if (var[0] == '?')
		value = replace_special_signs(var);
	return (value);
}

char	**replace_var(char *var, char **tokenizedInput)
{
	char	**expanded_array;
	int		i;
	char	*var_value;
	char	*trimmed;

	i = -1;
	expanded_array = ft_calloc(ft_2d_array_len(tokenizedInput) + 1, \
		sizeof(char *));
	if (!expanded_array)
		return (NULL);
	while (tokenizedInput[++i])
	{
		trimmed = remove_quotes(tokenizedInput[i], '\"');
		if ((trimmed[0] != '$' && trimmed[1] != '$') || trimmed[1] == '\0')
			expanded_array[i] = ft_strdup(tokenizedInput[i]);
		else
		{
			var_value = find_var(var);
			if (var_value)
				expanded_array[i] = var_value;
			else
				expanded_array[i] = ft_strdup(" ");
		}
	}
	return (free(var), expanded_array);
}

char	**remove_empty_elements(char **arr)
{
	int		i;
	int		j;
	char	**new_arr;

	i = 0;
	j = 0;
	new_arr = ft_calloc(ft_2d_array_len(arr) + 1, sizeof(char *));
	if (!new_arr)
		return (NULL);
	while (arr[i])
	{
		if (arr[i][0] != ' ')
		{
			new_arr[j] = ft_strdup(arr[i]);
			j++;
		}
		i++;
	}
	ft_free_2d_array(&arr);
	return (new_arr);
}

char	**find_env_var_and_replace(char *var, char **tokenizedInput)
{
	char	*tmp_var;
	char	*tmp;
	int		j;
	char	**res;
	char	**trimmed;

	j = 0;
	res = NULL;
	tmp_var = ft_calloc(ft_strlen(var) + 1, sizeof(char));
	if (!tmp_var)
		return (NULL);
	tmp = remove_quotes(var, '\"');
	if (has_single_quoting(var))
		tmp_var = ft_strdup(var);
	else
	{
		while (*tmp)
			tmp_var[j++] = *++tmp;
		tmp_var[j] = '\0';
	}
	res = replace_var(tmp_var, tokenizedInput);
	if (!res)
		return (free(tmp_var), NULL);
	trimmed = remove_empty_elements(res);
	return (trimmed);
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
		if (has_single_quoting(temp_token_array[i]) && i == 0 && \
			ft_2d_array_len(temp_token_array) > 1)
				i++;
		if (ft_strchr(temp_token_array[i], '$') != NULL && \
			!has_single_quoting(temp_token_array[i]))
		{
			replaced = find_env_var_and_replace(temp_token_array[i],
					tokenizedInput);
			if (replaced)
				last_str = manage_replaced(replaced, last_str);
		}
	}
	return (last_str);
}
