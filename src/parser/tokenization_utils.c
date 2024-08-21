/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:26:21 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 17:53:05 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quote(char c, int *in_quote, char *quote_char)
{
	if (*in_quote && c == *quote_char)
		*in_quote = 0;
	else if (!*in_quote)
	{
		*in_quote = 1;
		*quote_char = c;
	}
}

static const char	*skip_spaces(const char *str)
{
	while (*str && ft_is_space(*str))
		str++;
	return (str);
}

int	count_tokens(const char *str)
{
	int		count;
	int		in_quote;
	char	quote_char;

	count = 0;
	in_quote = 0;
	quote_char = '\0';
	while (*str)
	{
		str = skip_spaces(str);
		if (*str)
			count++;
		while (*str && (!ft_is_space(*str) || in_quote))
		{
			if (ft_is_quote(*str))
				handle_quote(*str, &in_quote, &quote_char);
			str++;
		}
	}
	return (count);
}
