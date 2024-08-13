/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_paired_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 16:56:48 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/12 16:57:17 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_remove_paired_quotes(char *str)
{
	int	src_idx;
	int	dest_idx;
	int	single_quote_open;
	int	double_quote_open;

	src_idx = 0;
	dest_idx = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	if (!str)
		return (NULL);
	while (str[src_idx])
	{
		if (str[src_idx] == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (str[src_idx] == '\"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		else
			str[dest_idx++] = str[src_idx];
		src_idx++;
	}
	str[dest_idx] = '\0';
	return (str);
}
