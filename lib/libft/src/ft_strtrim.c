/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:57:45 by Jskehan           #+#    #+#             */
/*   Updated: 2023/11/20 19:43:16 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*result;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (start <= end && ft_strchr(set, s1[start]))
		start++;
	while (s1[end] && ft_strchr(set, s1[end]) && end >= start)
		end--;
	result = (char *)malloc((end - start + 2) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, &s1[start], end - start + 2);
	return (result);
}
