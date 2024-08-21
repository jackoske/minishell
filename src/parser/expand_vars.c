/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:44 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/21 19:54:11 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_env_variables(char *str)
{
	char	*env_value;
	char	*result;
	int		index[3];

	result = (char *)malloc(strlen(str) * 2 + 1);
	if (!result)
		return (0);
	index[0] = ((index[1] = 0), (env_value = NULL), 0);
	while (str[index[0]])
	{
		if (str[index[0]] == '$')
		{
			index[0]++;
			index[2] = 0;
			manage_replacing(index, str, &env_value);
			if (env_value)
				index[1] = if_env(env_value, str, &result, index);
		}
		else
			result[index[1]++] = str[index[0]++];
	}
	result[index[1]] = '\0';
	return (result);
}

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
	char	*trimmed;

	i = -1;
	expanded_array = ft_calloc(ft_2d_array_len(tokenizedInput) + 1,
			sizeof(char *));
	if (!expanded_array)
		return (NULL);
	while (tokenizedInput[++i])
	{
		trimmed = remove_quotes(tokenizedInput[i], '\"');
		if (ft_strchr(trimmed, '$') == NULL || trimmed[1] != '\0')
		{
			expanded_array[i] = \
				ft_strdup(replace_env_variables(tokenizedInput[i]));
			if (ft_strchr(expanded_array[i], '$') != NULL
				&& ft_strcmp(expanded_array[i], tokenizedInput[i]) == 0)
				expanded_array[i] = ft_strdup(" ");
		}
		else
			expanded_array[i] = ft_strdup(tokenizedInput[i]);
	}
	return (free(var), expanded_array);
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
			tmp_var[j++] = *tmp++;
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
		if (has_single_quoting(temp_token_array[i]) && i == 0)
			i++;
		if (ft_strchr(temp_token_array[i], '$') != NULL
			&& !has_single_quoting(temp_token_array[i]))
		{
			replaced = find_env_var_and_replace(temp_token_array[i],
					tokenizedInput);
			if (replaced)
				last_str = manage_replaced(replaced, last_str);
		}
	}
	return (last_str);
}
