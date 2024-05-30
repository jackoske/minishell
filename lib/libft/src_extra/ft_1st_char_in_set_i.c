/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1st_char_in_set_i.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:33:08 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/28 18:27:06 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function: ft_1st_char_in_set_i
 * ----------------------------
 * Returns the index of the first character in a string that is in a set.
 *
 * @param str: The string to search.
 * @param set: The set of characters to search for.
 *
 * @return: The index of the first character in the string that is in the set.
 *          If no character in the string is in the set, returns -1.
 */
int	ft_1st_char_in_set_i(const char *str, const char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(set, str[i]))
			return (i);
		i++;
	}
	return (-1);
}
