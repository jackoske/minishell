	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:46:05 by iverniho          #+#    #+#             */
/*   Updated: 2024/06/10 14:17:01 by iverniho         ###   ########.fr       */
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

static void	define_symbol_len(int *len, char index1, char index2)
{
	*len = 1;
	if ((index1 == '<' && index2 == '<') || (index1 == '>' && index2 == '>')
		|| (index1 == '|' && index2))
		*len = 2;
}

void allocate_and_copy_token(char **tokens, int token_count, const char *str, int i, int *c)
{
	tokens[token_count] = malloc((*c + 1) * sizeof(char));
	ft_strlcpy(tokens[token_count], &str[i], *c + 1);
	tokens[token_count][*c] = '\0';
}

// void allocate_and_copy_token1(char **tokens, int token_count, const char *str, int i, int *c)
// {
// 	tokens[token_count] = malloc((c[1] + 1) * sizeof(char));
// 	ft_strlcpy(tokens[token_count], &str[i], c[1] + 1);
// 	tokens[token_count][c[1]] = '\0';
// }
	// c[0] = int		symbol_len;
	// c[1] = int		word_len;
/*Function to separate a string into tokens based on special symbols*/
char	**tokenize_special_symbols(const char *str, int i, int token_count)
{
	char	**tokens;
	int		c[2];
	int		len;
	int		start;

	if (!(tokens = (len = ft_strlen(str), ft_calloc(100, sizeof(char *)))))
		return (NULL);
	while (i < len && ++token_count <= 1000)
	{
		if (ft_is_special_symbol(str[i]))
		{
			define_symbol_len(&c[0], str[i], str[i + 1]);
			allocate_and_copy_token(tokens, token_count, str, i, &c[0]);
			i += c[0];
		}
		else
		{
			start = i;
			while (i < len && !ft_is_space(str[i]) && !ft_is_special_symbol(str[i]))
				i++;
			c[1] = i - start;
			allocate_and_copy_token(tokens, token_count, str, start, &c[1]);
		}
	}
	// printf("test1\n");
	// ft_print_2d_array_fd(tokens, 1);
	return (tokens);
}

// char	**tokenize_special_symbols(const char *str)
// {
// 	char	**tokens;
// 	int		token_count;
// 	int		i;
// 	int		len;
// 	int		symbol_len;
// 	int		start;
// 	int		word_len;

// 	token_count = 0;
// 	tokens = ft_calloc(100, sizeof(char *));
// 	if (!tokens)
// 		return (NULL);
// 	i = 0;
// 	len = ft_strlen(str);
// 	while (i < len)
// 	{
// 		if (ft_is_space(str[i]))
// 		{
// 			i++;
// 			continue ;
// 		}
// 		if (ft_is_special_symbol(str[i]))
// 		{
// 			symbol_len = 1;
// 			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i
// 					+ 1] == '>')/* || (str[i] == '|' && str[i + 1])*/)
// 				symbol_len = 2;
// 			tokens[token_count] = malloc((symbol_len + 1) * sizeof(char));
// 			ft_strlcpy(tokens[token_count], &str[i], symbol_len + 1);
// 			tokens[token_count][symbol_len] = '\0';
// 			token_count++;
// 			i += symbol_len;
// 		}
// 		else
// 		{
// 			start = i;
// 			while (i < len && !ft_is_space(str[i])
// 				&& !ft_is_special_symbol(str[i]))
// 				i++;
// 			word_len = i - start;
// 			tokens[token_count] = malloc((word_len + 1) * sizeof(char));
// 			ft_strlcpy(tokens[token_count], &str[start], word_len + 1);
// 			tokens[token_count][word_len] = '\0';
// 			token_count++;
// 		}
// 	}
// 	return (tokens);
// }
int	init_tokenize_input_vars(char ***tempTokenArray, \
	char ***specialSymbolArray, char ***expandedArray, char ***tokenizedInput)
{
	*tempTokenArray = NULL;
	*specialSymbolArray = NULL;
	*expandedArray = NULL;
	*tokenizedInput = NULL;
	return(-1);
}
void add_special_row(char ***tempTokenArray, char *specialSymbolArray, int *i)
{
	*tempTokenArray = ft_add_row_2d_array(*tempTokenArray, specialSymbolArray);
	*i += 1;
}
/*splits by spaces, taking quotted elements into consideration*/
char	**tokenize_input(char *input, t_mini **mini)
{
	char	**tokenizedInput;
	char	**expandedArray;
	char	**tempTokenArray;
	char	**specialSymbolArray;
	int		i[2];

	i[0] = init_tokenize_input_vars(&tempTokenArray, &specialSymbolArray, &expandedArray, &tokenizedInput);
	tokenizedInput = split_by_spaces(input, ft_word_count_quotes(ft_strtrim(input, " ")));
	expandedArray = expand_vars(tokenizedInput, mini);
	while (expandedArray[++i[0]])
	{
		if (ft_1st_char_in_set_i(expandedArray[i[0]], "<>|") != -1 && !ft_is_only_special(expandedArray[i[0]]) )
		{
			specialSymbolArray = NULL;
			specialSymbolArray = ft_splice_2d_array(specialSymbolArray,
					tokenize_special_symbols(expandedArray[i[0]], 0, -1), ft_2d_array_len(specialSymbolArray));
			i[1] = -1;
			while (specialSymbolArray[++i[1]])
				add_special_row(&tempTokenArray, specialSymbolArray[i[1]], &i[0]);
			i[0] -= 2;
		}
		else
			tempTokenArray = ft_add_row_2d_array(tempTokenArray, expandedArray[i[0]]);
	}
	ft_free_2d_array(&specialSymbolArray);
	return (ft_add_row_2d_array(tempTokenArray, NULL));
}

// char	**tokenize_input(char *input, t_mini **mini)
// {
// 	char	**tokenizedInput;
// 	char	**expandedArray;
// 	char	**tempTokenArray;
// 	char	**specialSymbolArray;
// 	int		i;
// 	int		k;

// 	i = ((expandedArray = NULL), (tokenizedInput = NULL), -1);
// 	tokenizedInput = split_by_spaces(input, ft_word_count_quotes(ft_strtrim(input,
// 					" ")));
// 	expandedArray = expand_vars(tokenizedInput, mini);
// 	specialSymbolArray = NULL;
// 	tempTokenArray = NULL;
// 	while (expandedArray[++i])
// 	{
// 		if (ft_1st_char_in_set_i(expandedArray[i], "<>|") != -1 && !ft_is_only_special(expandedArray[i]) )
// 		{
// 			specialSymbolArray = NULL;
// 			specialSymbolArray = ft_splice_2d_array(specialSymbolArray,
// 					tokenize_special_symbols(expandedArray[i], 0, -1), ft_2d_array_len(specialSymbolArray));
// 			k = -1;
// 			while (specialSymbolArray[++k])
// 			{
// 				tempTokenArray = ft_add_row_2d_array(tempTokenArray,
// 						specialSymbolArray[k]);
// 				i++;
// 			}
// 			i -= 2;
// 		}
// 		else
// 			tempTokenArray = ft_add_row_2d_array(tempTokenArray, expandedArray[i]);
// 	}
// 	ft_free_2d_array(&specialSymbolArray);
// 	tempTokenArray = ft_add_row_2d_array(tempTokenArray, NULL);
// 	ft_print_2d_array_fd(tempTokenArray, 1);
// 	return (tempTokenArray);
// }
// char	**tokenize_input(char *input, t_mini **mini)
// {
// 	char	**tokenizedInput;
// 	char	**expandedArray;
// 	char	**tempTokenArray;
// 	char	**specialSymbolArray;
// 	int		i;
// 	int		k;

// 	i = ((expandedArray = NULL), (tokenizedInput = NULL),
// 			-1);
// 	tokenizedInput = split_by_spaces(input, ft_word_count_quotes(ft_strtrim(input,
// 					" ")));
// 	expandedArray = expand_vars(tokenizedInput, mini);
// 	specialSymbolArray = NULL;
// 	tempTokenArray = NULL;
// 	while (expandedArray[++i])
// 	{
// 		if (ft_1st_char_in_set_i(expandedArray[i], "<>|") != -1 && !ft_is_only_special(expandedArray[i]) )
// 		{
// 			specialSymbolArray = NULL;
// 			specialSymbolArray = ft_splice_2d_array(specialSymbolArray,
// 					tokenize_special_symbols(expandedArray[i], 0, -1), ft_2d_array_len(specialSymbolArray));
// 			k = -1;
// 			while (specialSymbolArray[++k])
// 			{
// 				tempTokenArray = ft_add_row_2d_array(tempTokenArray,
// 						specialSymbolArray[k]);
// 				i++;
// 			}
// 			i -= 2;
// 		}
// 		else
// 			tempTokenArray = ft_add_row_2d_array(tempTokenArray, expandedArray[i]);
// 	}
// 	ft_free_2d_array(&specialSymbolArray);
// 	tempTokenArray = ft_add_row_2d_array(tempTokenArray, NULL);
// 	// ft_print_2d_array_fd(tempTokenArray, 1);
// 	return (tempTokenArray);
// }
