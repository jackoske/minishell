/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:33:17 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/21 17:24:25 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*handle_special_symbol(const char *str, int *i)
{
	int		len;
	char	*token;

	len = 1;
	if ((str[*i] == '>' || str[*i] == '<') && str[*i + 1] == str[*i])
		len++;
	token = ft_substr(str, *i, len);
	*i += len;
	return (token);
}

char	**tokenize_sp_symb(const char *str, int i, int token_count)
{
	char	**tokens;
	int		start;

	tokens = malloc(100 * sizeof(char *));
	if (!tokens)
		return (NULL);
	while (str[i] && token_count < 100)
	{
		if (ft_is_special_symbol(str[i]))
			tokens[token_count++] = handle_special_symbol(str, &i);
		else
		{
			start = i;
			while (str[i] && !ft_is_special_symbol(str[i]))
				i++;
			tokens[token_count++] = ft_substr(str, start, i - start);
		}
	}
	tokens[token_count] = NULL;
	return (tokens);
}

static char	**process_special_symbols(char *token, char **tmpTokArr)
{
	char	**split_tokens;
	int		i;

	split_tokens = tokenize_sp_symb(token, 0, 0);
	if (!split_tokens)
		return (NULL);
	i = 0;
	while (split_tokens[i])
	{
		tmpTokArr = ft_add_row_2d_array(tmpTokArr, split_tokens[i], 0);
		if (!tmpTokArr)
		{
			ft_free_2d_array(&split_tokens);
			return (NULL);
		}
		i++;
	}
	ft_free_2d_array(&split_tokens);
	return (tmpTokArr);
}

char	**process_expanded_array(char **expandedArray, char **tmpTokArr)
{
	int	i;

	i = 0;
	while (expandedArray[i])
	{
		if (ft_is_string_quoted(expandedArray[i]))
			tmpTokArr = ft_add_row_2d_array(tmpTokArr, expandedArray[i], 0);
		else if (ft_contains_special_symbols(expandedArray[i]))
		{
			tmpTokArr = process_special_symbols(expandedArray[i], tmpTokArr);
			if (!tmpTokArr)
				return (NULL);
		}
		else
			tmpTokArr = ft_add_row_2d_array(tmpTokArr, expandedArray[i], 0);
		if (!tmpTokArr)
		{
			printf("Error processing token: %s\n", expandedArray[i]);
			return (NULL);
		}
		i++;
	}
	return (tmpTokArr);
}
