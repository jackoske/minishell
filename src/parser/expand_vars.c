/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:44 by iverniho          #+#    #+#             */
/*   Updated: 2024/07/16 15:47:40 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(char *var, t_mini **mini)
{
	int		i;
	char	*value;
	int		var_len;

	i = 0;
	value = NULL;
	var_len = ft_strlen(var);
	while ((*mini)->envp[i])
	{
		if (ft_strncmp((*mini)->envp[i], var, var_len) == 0 &&
			(*mini)->envp[i][var_len] == '=')
		{
			value = ft_strdup((*mini)->envp[i] + var_len + 1);
			break ;
		}
		i++;
	}
	return (value);
}

// echo "hello      there" how are  $USER |wc -l >outfile
char	**find_env_var_and_replace(char *var, t_mini **mini,
		char **tokenizedInput)
{
	char	*tempTokenArray;
	int		i;
	int		j;
	char	**expandedArray;

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
			char *var_value = find_var(tempTokenArray, mini);
			if (var_value)
				expandedArray[i] = var_value;
			else
				expandedArray[i] = ft_strdup(tokenizedInput[i]);
		}
	}
	free(tempTokenArray);
	return (expandedArray);
}

char	**expand_vars(char **tokenizedInput, t_mini **mini)
{
	char	**tempTokenArray;
	char	**last_str;
	int		i;

	tempTokenArray = ft_duplicate_2d_array(tokenizedInput);
	if (!tempTokenArray)
		return (NULL);
	last_str = tempTokenArray;
	i = -1;
	while (tempTokenArray[++i])
	{
		if (ft_strchr(tempTokenArray[i], '$') != NULL)
		{
			char **replaced = find_env_var_and_replace(tempTokenArray[i], mini, tokenizedInput);
			if (replaced)
			{
				ft_free_2d_array(&last_str);
				last_str = replaced;
			}
		}
	}
	return (last_str);
}
