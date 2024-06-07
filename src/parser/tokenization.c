/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:46:05 by iverniho          #+#    #+#             */
/*   Updated: 2024/06/07 17:50:17 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**populateTokenArray(char **tokenizedInput, char *input)
{
	int		k;
	int		quote[2];
	int		begin;
	int		end;

	quote[0] = ((quote[1] = 0), (begin = 0), (end = 0), (k = 0), 0);
	while (input[end])
	{
		while (ft_strchr(" ", input[end]) && input[end] != '\0')
			end++;
		begin = end;
		while ((!ft_strchr(" ", input[end]) || quote[0] || quote[1])
			&& input[end])
		{
			quote[0] = (quote[0] + (!quote[1] && input[end] == '\'')) % 2;
			quote[1] = (quote[1] + (!quote[0] && input[end] == '\"')) % 2;
			end++;
		}
		if (begin >= (int)ft_strlen(input))
			tokenizedInput[k++] = "\0";
		else
			tokenizedInput[k++] = ft_substr(input, begin, end - begin);
		}
	tokenizedInput[k] = NULL;
	return (tokenizedInput);
}

char	**split_by_spaces(char *input, int w_count)
{
	char	**tokenizedInput;

	tokenizedInput = ft_calloc( w_count + 1, sizeof(char *));
	if (!tokenizedInput)
		return (NULL);
	tokenizedInput = populateTokenArray(tokenizedInput, input);
	return (tokenizedInput);
}

/*Function to separate a string into tokens based on special symbols*/
char	**tokenize_special_symbols(const char *str)
{
	char	**tokens;
	int		token_count;
	int		i;
	int		len;
	int		symbol_len;
	int		start;
	int		word_len;

	token_count = 0;
	tokens = ft_calloc(100, sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (ft_is_space(str[i]))
		{
			i++;
			continue ;
		}
		if (ft_is_special_symbol(str[i]))
		{
			symbol_len = 1;
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i
					+ 1] == '>'))
				symbol_len = 2;
			tokens[token_count] = malloc((symbol_len + 1) * sizeof(char));
			ft_strlcpy(tokens[token_count], &str[i], symbol_len + 1);
			tokens[token_count][symbol_len] = '\0';
			token_count++;
			i += symbol_len;
		}
		else
		{
			start = i;
			while (i < len && !ft_is_space(str[i])
				&& !ft_is_special_symbol(str[i]))
				i++;
			word_len = i - start;
			tokens[token_count] = malloc((word_len + 1) * sizeof(char));
			ft_strlcpy(tokens[token_count], &str[start], word_len + 1);
			tokens[token_count][word_len] = '\0';
			token_count++;
		}
	}
	return (tokens);
}

/*splits by spaces, taking quotted elements into consideration*/
char	**tokenize_input(char *input, t_mini **mini)
{
	char	**tokenizedInput;
	char	**expandedArray;
	char	**tempTokenArray;
	char	**specialSymbolArray;
	int		i;
	int		j;
	int		k;

	j = ((i = -1), (k = -1), (expandedArray = NULL), (tokenizedInput = NULL),
			-1);
	tokenizedInput = split_by_spaces(input, ft_word_count_quotes(ft_strtrim(input,
					" ")));
	expandedArray = expand_vars(tokenizedInput, mini);
	specialSymbolArray = NULL;
	tempTokenArray = NULL;
	while (expandedArray[++i])
	{
		if (ft_1st_char_in_set_i(expandedArray[i], "<>|") != -1 && !ft_is_only_special(expandedArray[i]) )
		{
			specialSymbolArray = ft_splice_2d_array(specialSymbolArray,
					tokenize_special_symbols(expandedArray[i]), ft_2d_array_len(specialSymbolArray));
			ft_print_2d_array_fd(specialSymbolArray, 1);
			j = -1;
			while (specialSymbolArray[++j])
			{
				tempTokenArray = ft_add_row_2d_array(tempTokenArray,
						specialSymbolArray[j]);
				i++;
			}
			i -= 2;
		}
		else
			tempTokenArray = ft_add_row_2d_array(tempTokenArray, expandedArray[i]);
	}
	tempTokenArray = ft_add_row_2d_array(tempTokenArray, NULL);
	return (tempTokenArray);
}
