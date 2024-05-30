/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:36:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/29 18:08:39 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Function: ft_is_space
 * ---------------------
 * Checks if a character is a space character.
 *
 * @param c: The character to check.
 *
 * @return: 1 if the character is a space character, 0 otherwise.
 */
int	ft_is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}
