/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:46:05 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/05 20:53:58 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Populate Token Array Function
char	**populateTokenArray(char **tokenizedInput, char *input)
{
	int	k;
	int	quote[2];
	int	begin;
	int	end;

	quote[0] = quote[1] = begin = end = k = 0;
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

// Split by Spaces Function
char	**split_by_spaces(char *input, int w_count)
{
	char	**tokenizedInput;

	tokenizedInput = ft_calloc(w_count + 1, sizeof(char *));
	if (!tokenizedInput)
		return (NULL);
	tokenizedInput = populateTokenArray(tokenizedInput, input);
	return (tokenizedInput);
}

// Define Symbol Length Function
static void	define_symbol_len(int *len, char index1, char index2)
{
	*len = 1;
	if ((index1 == '<' && index2 == '<') || (index1 == '>' && index2 == '>'))
		*len = 2;
}

// Allocate and Copy Token Function
void	allocate_and_copy_token(char **tokens, int token_count, const char *str,
		int i, int c)
{
	tokens[token_count] = malloc((c + 1) * sizeof(char));
	if (!tokens[token_count])
		return ;
	ft_strlcpy(tokens[token_count], &str[i], c + 1);
	tokens[token_count][c] = '\0';
}

// Tokenize Special Symbols Function
char	**tokenize_special_symbols(const char *str, int i, int token_count)
{
	char	**tokens;
	int		c[2];
	int		len;
	int		start;

	tokens = ft_calloc(100, sizeof(char *));
	if (!tokens)
		return (NULL);
	len = ft_strlen(str);
	while (i < len && ++token_count <= 1000)
	{
		if (ft_is_special_symbol(str[i]))
		{
			define_symbol_len(&c[0], str[i], str[i + 1]);
			allocate_and_copy_token(tokens, token_count, str, i, c[0]);
			i += c[0];
		}
		else
		{
			start = i;
			while (i < len && !ft_is_space(str[i])
				&& !ft_is_special_symbol(str[i]))
				i++;
			c[1] = i - start;
			allocate_and_copy_token(tokens, token_count, str, start, c[1]);
		}
	}
	return (tokens);
}

// Initialize Tokenize Input Variables Function
int	init_tokenize_input_vars(char ***tempTokenArray, char ***specialSymbolArray,
		char ***expandedArray, char ***tokenizedInput)
{
	*tempTokenArray = NULL;
	*specialSymbolArray = NULL;
	*expandedArray = NULL;
	*tokenizedInput = NULL;
	return (-1);
}

// Add Special Row Function
void	add_special_row(char ***tempTokenArray, char *specialSymbolArray,
		int *i)
{
	*tempTokenArray = ft_add_row_2d_array(*tempTokenArray, specialSymbolArray,
			0);
	*i += 1;
}

// Tokenize Input Function
char	**tokenize_input(char *input)
{
	char	**tokenizedInput;
	char	**expandedArray;
	char	**tempTokenArray;
	char	**specialSymbolArray;
	char	*trimmedInput;
	int		i[2];

	init_tokenize_input_vars(&tempTokenArray, &specialSymbolArray,
		&expandedArray, &tokenizedInput);
	trimmedInput = ft_strtrim(input, " ");
	tokenizedInput = split_by_spaces(trimmedInput,
			ft_word_count_quotes(trimmedInput));
	free(trimmedInput);
	if (!tokenizedInput)
		return (NULL);
	expandedArray = expand_vars(tokenizedInput);
	if (!expandedArray)
	{
		ft_free_2d_array(&tokenizedInput);
		return (NULL);
	}
	i[0] = -1;
	while (expandedArray[++i[0]])
	{
		if (ft_1st_char_in_set_i(expandedArray[i[0]], "<>|") != -1
			&& !ft_is_only_special(expandedArray[i[0]]))
		{
			specialSymbolArray = ft_splice_2d_array(specialSymbolArray,
					tokenize_special_symbols(expandedArray[i[0]], 0, -1),
					ft_2d_array_len(specialSymbolArray));
			if (!specialSymbolArray)
			{
				ft_free_2d_array(&expandedArray);
				ft_free_2d_array(&tempTokenArray);
				return (NULL);
			}
			i[1] = -1;
			while (specialSymbolArray[++i[1]])
			{
				add_special_row(&tempTokenArray, specialSymbolArray[i[1]],
					&i[0]);
			}
			i[0] -= 2;
		}
		else
		{
			tempTokenArray = ft_add_row_2d_array(tempTokenArray,
					expandedArray[i[0]], 0);
		}
	}
	ft_free_2d_array(&specialSymbolArray);
	ft_free_2d_array(&expandedArray);
	ft_free_2d_array(&tokenizedInput);
	return (ft_add_row_2d_array(tempTokenArray, NULL, 1));
}
