/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:44 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/21 19:26:59 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_sprintf(int *src_idx)
{
	char	*env_value;

	env_value = ft_strdup( ft_itoa(g_mini->exit_status));
	*src_idx += 1;
	return (env_value);
}

char	*imp_while1(char *str, int *src_idx, int *var_idx)
{
	char	*env_value;
	char	var_name[100];
	int		j;
	int		k;

	while (str[(*src_idx)] && (ft_isalnum(str[(*src_idx)]) || str[(*src_idx)] == '_'))
	{
		var_name[(*var_idx)++] = str[(*src_idx)++];
		var_name[(*var_idx)] = '\0';
		env_value = getenv(var_name);
		if (env_value)
			break;
	}
	var_name[(*var_idx)] = '\0';
	env_value = ((j = -1), (k = -1), NULL);
	env_value = getenv(var_name);
	if (!env_value)
	{

		env_value = (char *)malloc(ft_strlen(var_name) + 2);
		env_value[++k] = '$';
		while (var_name[++j])
			env_value[++k] = var_name[j];
		env_value[++k] = '\0';
	}
	return (env_value);
}

int if_env(char *env_value, char *str, char **result, int *index)
{
	int env_len;
	if (env_value)
	{
		env_len = strlen(env_value);
		if (index[1] + env_len >= (int)ft_strlen(str) * 2)
		{
			(*result) = ft_realloc((*result), index[1] + env_len + 1);
			if (!(*result))
				return (0);
		}
		while (*env_value)
			(*result)[index[1]++] = *env_value++;
	}
	else
		(*result)[index[1]++] = str[index[0]++];
	return index[1];
}

void manage_replacing(int *index, char *str, char **env_value)
{
	if (str[index[0]] == '?')
		(*env_value) = handle_sprintf(&index[0]);
	else
		(*env_value) = imp_while1( str, &index[0], &index[2]);
}

char *replace_env_variables(char *str)
{
	char *env_value;
	char *result;
	int index[3];

	result = (char *)malloc(strlen(str) * 2 + 1);
	if (!result)
		return (0);
	index[0] =((index[1] = 0),(env_value = NULL), 0);
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
///////////////////////////////////////////////////////////////////////////////////////////////
//working version
// char *replace_env_variables(const char *str)
// {
// 	int src_idx = 0, dest_idx = 0;
// 	char *result;
// 	char var_name[100];
// 	int var_idx;
// 	char *env_value;
// 	char exitcode[12];

// 	result = (char *)malloc(strlen(str) * 2 + 1);
// 	if (!result)
// 		return NULL;

// 	while (str[src_idx])
// 	{
// 		if (str[src_idx] == '$')
// 		{
// 			src_idx++;
// 			var_idx = 0;

// 			if (str[src_idx] == '?')
// 			{
// 				snprintf(exitcode, sizeof(exitcode), "%d", g_mini->exit_status);
// 				env_value = exitcode;
// 				src_idx++;
// 			}
// 			else
// 			{
// 				while (str[src_idx] && (ft_isalnum(str[src_idx]) || str[src_idx] == '_'))
// 				{
// 					var_name[var_idx++] = str[src_idx++];
// 					var_name[var_idx] = '\0';
// 					env_value = getenv(var_name);
// 					if (env_value)
// 						break;
// 				}
// 				var_name[var_idx] = '\0';
// 				env_value = NULL;
// 				env_value = getenv(var_name);
// 				if (!env_value)
// 				{
// 					int j = -1;
// 					int k = -1;
// 					env_value = (char *)malloc(ft_strlen(var_name) + 2);
// 					env_value[++k] = '$';
// 					while (var_name[++j])
// 					{
// 						env_value[++k] = var_name[j];
// 					}
// 					env_value[++k] = '\0';
// 				}
// 			}
// 			if (env_value)
// 			{
// 				int env_len = strlen(env_value);
// 				if (dest_idx + env_len >= (int)ft_strlen(str) * 2)
// 				{
// 					result = ft_realloc(result, dest_idx + env_len + 1);
// 					if (!result)
// 						return NULL;
// 				}
// 				while (*env_value)
// 					result[dest_idx++] = *env_value++;
// 			}
// 			else
// 				result[dest_idx++] = str[src_idx++];
// 		}
// 		else
// 			result[dest_idx++] = str[src_idx++];
// 	}
// 	result[dest_idx] = '\0';
// 	return result;

// }
/////////////////////////////////////////////////////////////////////////////////////////


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
		if (ft_strchr(trimmed, '$') == NULL  || trimmed[1] != '\0')
		{
			expanded_array[i] = ft_strdup(replace_env_variables(tokenizedInput[i]));
			if (ft_strchr(expanded_array[i], '$') != NULL && ft_strcmp(expanded_array[i], tokenizedInput[i]) == 0)
				expanded_array[i] = ft_strdup(" ");
		}
		else
			expanded_array[i] = ft_strdup(tokenizedInput[i]);
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
