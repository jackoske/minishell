/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:16:26 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/28 17:17:02 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function: ft_count_char
 * -----------------------
 * Counts the number of occurrences of a character in a string.
 *
 * @param str: The string to search.
 * @param c: The character to count.
 *
 * @return: The number of occurrences of the character in the string.
 */

int	ft_count_char(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
