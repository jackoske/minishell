/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:46:05 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/07 19:46:20 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Populate Token Array Function
char	**populate_token_array(char **tokenizedInput, char *input)
{
	int	k;
	int	quote[2];
	int	begin;
	int	end;

	quote[0] = ((quote[1] = 0, begin = 0, end = 0), k = 0);
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
char	**split_spaces(char *input, int w_count)
{
	char	**tokenized_input;

	tokenized_input = ft_calloc(w_count + 1, sizeof(char *));
	if (!tokenized_input)
		return (NULL);
	tokenized_input = populate_token_array(tokenized_input, input);
	return (tokenized_input);
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

char	**tokenize_sp_symb(const char *str, int i, int token_count)
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
// int	init_tokenize_input_vars(char ***tempTokenArray, char ***specialSymbolArray,\
// 		char ***expandedArray, char ***tokenizedInput)
// {
// 	*tempTokenArray = NULL;
// 	*specialSymbolArray = NULL;
// 	*expandedArray = NULL;
// 	*tokenizedInput = NULL;
// 	return (-1);
// }

// Add Special Row Function
void	add_special_row(char ***tempTokenArray, char *specialSymbolArray,
		int *i)
{
	*tempTokenArray = ft_add_row_2d_array(*tempTokenArray, specialSymbolArray,
			0);
	*i += 1;
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

static char	**process_special_symb(char *token, char **tempTokenArr, int *i)
{
	char	**sp_sym_arr;
	int		j;

	sp_sym_arr = ft_splice_2d_array(NULL, tokenize_sp_symb(token, 0, -1), 0);
	if (!sp_sym_arr)
		return (ft_free_2d_array(&tempTokenArr), NULL);
	j = -1;
	while (sp_sym_arr[++j])
		add_special_row(&tempTokenArr, sp_sym_arr[j], i);
	free(sp_sym_arr);
	return (tempTokenArr);
}

static char	**process_expanded_array(char **expandedArray, char **tmpTokArr)
{
	int	i;

	i = -1;
	while (expandedArray[++i])
	{
		if (is_string_quoted(expandedArray[i]))
			tmpTokArr = ft_add_row_2d_array1(tmpTokArr, expandedArray[i]);
		else if (ft_1st_char_in_set_i(expandedArray[i], "<>|") != -1
			&& !ft_is_only_special(expandedArray[i]))
		{
			tmpTokArr = process_special_symb(expandedArray[i], tmpTokArr, &i);
			if (!tmpTokArr)
				return (NULL);
			i -= 2;
		}
		else
			tmpTokArr = ft_add_row_2d_array(tmpTokArr, expandedArray[i], 0);
	}
	return (tmpTokArr);
}

char	**tokenize_input(char *input)
{
	char	**tok_input;
	char	**expanded_arr;
	char	**temp_token_arr;
	char	*trimmed_input;

	temp_token_arr = NULL;
	trimmed_input = ft_strtrim(input, " ");
	tok_input = split_spaces(trimmed_input, w_count_quotes(trimmed_input));
	free(trimmed_input);
	if (!tok_input)
		return (NULL);
	expanded_arr = expand_vars(tok_input);
	if (!expanded_arr)
		return (ft_free_2d_array(&tok_input), NULL);
	temp_token_arr = process_expanded_array(expanded_arr, temp_token_arr);
	if (!temp_token_arr)
	{
		ft_free_2d_array(&expanded_arr);
		ft_free_2d_array(&tok_input);
		return (NULL);
	}
	ft_free_2d_array(&expanded_arr);
	ft_free_2d_array(&tok_input);
	return (ft_add_row_2d_array(temp_token_arr, NULL, 1));
}
