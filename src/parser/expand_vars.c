/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:44 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/06 19:51:51 by iverniho         ###   ########.fr       */
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

// echo "hello      there" how are  $USER |wc -l >outfile
char	**find_env_var_and_replace(char *var, char **tokenizedInput)
{
	char	*tempTokenArray;
	int		i;
	int		j;
	char	**expandedArray;
	char	*var_value;

	tempTokenArray = ft_calloc(ft_strlen(var) + 1, sizeof(char));
	if (!tempTokenArray)
		return (NULL);
	expandedArray = ft_calloc(ft_2d_array_len(tokenizedInput) + 1,
			sizeof(char *));
	if (!expandedArray)
	{
		free(tempTokenArray);
		return (NULL);
	}
	j = 0;
	i = 0;
	while (var[i])
		tempTokenArray[j++] = var[i++];
	tempTokenArray[j] = '\0';
	i = -1;
	while (tokenizedInput[++i])
	{
		if (ft_strchr(tokenizedInput[i], '$') == NULL)
			expandedArray[i] = ft_strdup(tokenizedInput[i]);
		else
		{
			var_value = find_var(tempTokenArray);
			if (var_value)
				expandedArray[i] = var_value;
			else
				expandedArray[i] = ft_strdup(tokenizedInput[i]);
		}
	}
	free(tempTokenArray);
	return (expandedArray);
}

char	**expand_vars(char **tokenizedInput)
{
	char	**tempTokenArray;
	char	**last_str;
	int		i;
	char	**replaced;

	tempTokenArray = ft_duplicate_2d_array(tokenizedInput);
	if (!tempTokenArray)
		return (NULL);
	last_str = tempTokenArray;
	i = -1;
	while (tempTokenArray[++i])
	{
		if (ft_strchr(tempTokenArray[i], '$') != NULL
			&& (tempTokenArray[i][1] != '?'
				&& ft_strlen(tempTokenArray[i]) == 2))
		{
			replaced = find_env_var_and_replace(tempTokenArray[i],
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
