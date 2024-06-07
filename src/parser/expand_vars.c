/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:40:44 by iverniho          #+#    #+#             */
/*   Updated: 2024/06/07 17:41:55 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_var(char *var, t_mini **mini)
{
	int		i;
	char	*value;

	i = -1;
	value = NULL;
	while ((*mini)->envp[++i])
	{
		if (ft_strncmp((*mini)->envp[i], var, ft_strlen(var)) == 0)
		{
			value = ft_strdup((*mini)->envp[i] + ft_strlen(var) + 1);
			break ;
		}
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

	expandedArray = NULL;
	tempTokenArray = ft_calloc(ft_strlen(var) + 1, sizeof(char));
	expandedArray = ft_calloc(ft_2d_array_len(tokenizedInput) + 1,
			sizeof(char *));
	j = 0;
	i = 0;
	while (var[i++])
		tempTokenArray[j++] = var[i];
	tempTokenArray[j] = '\0';
	i = -1;
	while (tokenizedInput[++i])
	{
		if (ft_strchr(tokenizedInput[i], '$') == NULL)
			expandedArray[i] = ft_strdup(tokenizedInput[i]);
		else
			expandedArray[i] = find_var(tempTokenArray, mini);
	}
	return (expandedArray);
}

char	**expand_vars(char **tokenizedInput, t_mini **mini)
{
	char	**tempTokenArray;
	char	**last_str;
	int		i;

	tempTokenArray = NULL;
	last_str = NULL;
	i = -1;
	tempTokenArray = ft_duplicate_2d_array(tokenizedInput);
	if (!tempTokenArray)
		return (NULL);
	while (tempTokenArray[++i])
	{
		if (ft_strchr(tempTokenArray[i], '$') != NULL)
			last_str = find_env_var_and_replace(tokenizedInput[i], mini,
					tokenizedInput);
	}
	if (!last_str)
		return (tokenizedInput);
	return (last_str);
}
