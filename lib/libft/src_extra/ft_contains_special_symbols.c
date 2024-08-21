/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contains_special_symbols.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:13:36 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 17:14:19 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_contains_special_symbols(const char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '<' || *str == '>' || *str == '|')
			return (1);
		str++;
	}
	return (0);
}
