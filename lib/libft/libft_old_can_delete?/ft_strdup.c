/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:30:39 by iverniho          #+#    #+#             */
/*   Updated: 2024/05/21 16:08:54 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Duplicates the string 's'. Allocates sufficient memory for a copy of
 * the string 's', does the copy, and returns a pointer to it.
 *
 * @param s A pointer to the string to be duplicated.
 * @return Returns a pointer to the duplicated string, or NULL if
 *         memory allocation fails.
 */
char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*result;
	char	*start;

	size = ft_strlen(s);
	result = (char *)malloc((size + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	start = result;
	while (*s)
		*result++ = *s++;
	*result = '\0';
	return (start);
}
