/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:46:05 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/26 18:45:45 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_next_token(const char **str)
{
	const char	*start;
	char		*token;
	int			in_single_quote;
	int			in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (**str && ft_is_space(**str))
		(*str)++;
	start = *str;
	while (**str && (!ft_is_space(**str) || in_single_quote || in_double_quote))
	{
		if (**str == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (**str == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		(*str)++;
	}
	token = strndup(start, *str - start);
	return (token);
}

static char	**split_spaces(const char *str, int token_count)
{
	char	**tokens;
	int		i;

	if (!str)
		return (NULL);
	token_count = count_tokens(str);
	tokens = (char **)malloc((token_count + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	i = 0;
	while (i < token_count)
	{
		tokens[i] = get_next_token(&str);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

char	**tokenize_input(char *input)
{
	char	**tok_input;
	char	**expanded_arr;
	char	**final_tokens;

	tok_input = split_spaces(input, w_count_quotes(input));
	if (!tok_input)
		return (NULL);
	expanded_arr = expand_vars(ft_remove_quotes(tok_input));
	if (!expanded_arr)
	{
		ft_free_2d_array(&tok_input);
		return (NULL);
	}
	final_tokens = process_expanded_array(expanded_arr, NULL);
	ft_free_2d_array(&expanded_arr);
	ft_free_2d_array(&tok_input);
	if (!final_tokens)
		return (NULL);
	return (ft_add_row_2d_array(final_tokens, NULL, 1));
}
