/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:33:17 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/08 12:41:09 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocate_and_copy_token1(char **tokens,	int token_count, \
	const char *str, int c[5])
{
	tokens[token_count] = ft_calloc(c[0] + 1, sizeof(char));
	if (!tokens[token_count])
		return ;
	ft_strlcpy(tokens[token_count], &str[c[3]], c[0] + 1);
	tokens[token_count][c[0]] = '\0';
}

void	allocate_and_copy_token2(char **tokens, \
	int token_count, const char *str, int n[5])
{
	tokens[token_count] = ft_calloc(n[5] + 1, sizeof(char));
	if (!tokens[token_count])
		return ;
	ft_strlcpy(tokens[token_count], &str[n[4]], n[5] + 1);
	tokens[token_count][n[5]] = '\0';
}

void	imp_while(int *i, int len, const char *str, int *start)
{
	(*start) = (*i);
	while ((*i) < len && !ft_is_space(str[(*i)])
		&& !ft_is_special_symbol(str[(*i)]))
		(*i)++;
}

char	**ft_add_row_2d_array1(char **array, char *row)
{
	int		i;
	char	**new_array;

	i = 0;
	if (!array)
	{
		new_array = ft_calloc(2, sizeof(char *));
		if (!new_array)
			return (NULL);
		new_array[0] = ft_strdup(row);
		new_array[1] = NULL;
		return (new_array);
	}
	while (array[i])
		i++;
	new_array = ft_calloc(i + 2, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = -1;
	while (array[++i])
		new_array[i] = ft_strdup(array[i]);
	new_array[i] = ft_strdup(row);
	new_array[i + 1] = NULL;
	ft_free_2d_array(&array);
	return (new_array);
}

// Add Special Row Function
void	add_special_row(char ***tempTokenArray, char *specialSymbolArray, \
	int *i)
{
	*tempTokenArray = ft_add_row_2d_array(*tempTokenArray, specialSymbolArray,
			0);
	*i += 1;
}
