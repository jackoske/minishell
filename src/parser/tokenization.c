/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:46:05 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/12 15:52:38 by iverniho         ###   ########.fr       */
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

char	**tokenize_sp_symb(const char *str, int i, int token_count)
{
	char	**tokens;
	int		c[6];
	int		start;

	tokens = ((c[3] = i), ft_calloc(100, sizeof(char *)));
	if (!tokens)
		return (NULL);
	while (c[3] < (int)ft_strlen(str) && ++token_count <= 1000)
	{
		if (ft_is_special_symbol(str[c[3]]))
		{
			define_symbol_len(&c[0], str[c[3]], str[c[3] + 1]);
			allocate_and_copy_token1(tokens, token_count, str, c);
			c[3] += c[0];
		}
		else
		{
			imp_while(&c[3], ft_strlen(str), str, &start);
			c[4] = start;
			c[5] = c[3] - c[4];
			allocate_and_copy_token2(tokens, token_count, str, c);
		}
	}
	return (tokens);
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
		{
			// if (expandedArray[i][0] != ' ')
			// 	tmpTokArr = ft_add_row_2d_array(tmpTokArr, expandedArray[i], 0);
			tmpTokArr = ft_add_row_2d_array(tmpTokArr, expandedArray[i], 0);
		}
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
