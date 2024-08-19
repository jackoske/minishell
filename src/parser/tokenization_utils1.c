/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:38:19 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/19 16:04:59 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Split by Spaces Function
// char	**split_spaces(char *input, int w_count)
// {
// 	char	**tokenized_input;

// 	tokenized_input = ft_calloc(w_count + 1, sizeof(char *));
// 	if (!tokenized_input)
// 		return (NULL);
// 	tokenized_input = populate_token_array(tokenized_input, input);
// 	return (tokenized_input);
// }

// Define Symbol Length Function
void	define_symbol_len(int *len, char index1, char index2)
{
	*len = 1;
	if ((index1 == '<' && index2 == '<') || (index1 == '>' && index2 == '>'))
		*len = 2;
}
