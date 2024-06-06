/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:19:05 by Jskehan           #+#    #+#             */
/*   Updated: 2023/11/17 16:43:20 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
