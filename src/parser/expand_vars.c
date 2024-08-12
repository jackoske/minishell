/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:44 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/12 19:31:00 by iverniho         ###   ########.fr       */
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
	// printf("var1: %s\n", var);
	// printf("var[0]: %c\n", var[0]);
	// if (!var[0])
	// {
	// 	// printf("var is NULL\n");
	// 	return (NULL);
	// }
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
	// printf("value: %s\n", value);
	// if (!value)
	// {
	// 	value = ft_strdup(" ");
	// 	// printf("value: %s\n", value);
	// 	return (value);
	// }
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
	// printf("inside_rreplace var: %s\n", var);
	while (tokenizedInput[++i])
	{
		trimmed = remove_quotes(tokenizedInput[i], '\"');
		// if (ft_strchr(tokenizedInput[i], '$') == NULL)
		// printf("tokenizedInput[i]: %s\n", tokenizedInput[i]);
		// printf("trimmed: %s\n", trimmed);
		// if (ft_strcmp(trimmed, "$?") != 0)
			// show_last_command_status(g_mini->exit_status);
			// printf("exit_code: %d\n", g_mini->exit_status);
		if ((trimmed[0] != '$' && trimmed[1] != '$') || trimmed[1] == '\0')
		// if ((tokenizedInput[i][0] != '$' && tokenizedInput[i][1] != '$') || tokenizedInput[i][1] == '\0')
		// if (ft_strchr(remove_quotes(tokenizedInput[i], '\"'), '$') == NULL)
		{
			expanded_array[i] = ft_strdup(tokenizedInput[i]);
		}
		else
		{
			// printf("var: %s\n", var);
			var_value = find_var(var);
			// printf("var_value: %s\n", var_value);
			if (var_value)
				expanded_array[i] = var_value;
			else
				expanded_array[i] = ft_strdup(" ");
				// expanded_array[i] = ft_strdup(tokenizedInput[i]);
		}
	}
	free(var);
	return (expanded_array);
}

int	is_str_has_sigle_quottes(char *str)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quote++;
		i++;
	}
	if (quote % 2 == 0)
		return (1);
	return (0);
}

char **remove_empty_elements(char **arr)
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

int	has_single_quoting(const char *str)
{
	size_t len = strlen(str);

	if (len >= 2 && str[0] == '\'' && str[len - 1] == '\'') {
		return (1);
	}
	return (0);
}

char	**find_env_var_and_replace(char *var, char **tokenizedInput)
{
	char	*tmp_var;
	char	*tmp;
	int		j;
	char	**res;
	char	**trimmed;
	// int		i;

	j = 0;
	// i = -1;
	// printf("var: %s\n", var);
	res = NULL;
	tmp_var = ft_calloc(ft_strlen(var) + 1, sizeof(char));
	if (!tmp_var)
		return (NULL);
	tmp = remove_quotes(var, '\"');
	// printf("tmp: %s\n", tmp);
	// while (tmp[++i])
	// 	tmp_var[j++] = tmp[i];
	// free(tmp);
	// ft_print_2d_array_fd(tokenizedInput, 1);
	// ft_print_2d_array_fd(&tmp_var, 1);
	// printf("tmp_var: %s\n", tmp_var);
	// printf("has_single_quoting(tmp_var): %d\n", has_single_quoting(var));
	if (has_single_quoting(var))
	{
		// printf("has single quoting\n");
		// ft_print_2d_array_fd(tokenizedInput, 1);
		// printf("var: %s\n", var);
		tmp_var = ft_strdup(var);
		// return (tokenizedInput);
	}
	else
	{
		while (*tmp)
			tmp_var[j++] = *++tmp;
		tmp_var[j] = '\0';
	}

	res = replace_var(tmp_var, tokenizedInput);
	// printf("tmp_var: %s\n", tmp_var);
	// printf("test\n");
	if (!res)
		return (free(tmp_var), NULL);
	trimmed = remove_empty_elements(res);
	// ft_print_2d_array_fd(trimmed, 1);
	return (trimmed);
	// return (res);
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
			&& (temp_token_array[i][1] != '?'
			&& ft_strlen(temp_token_array[i]) != 2) &&
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
