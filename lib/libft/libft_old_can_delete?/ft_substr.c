/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 17:17:34 by iverniho          #+#    #+#             */
/*   Updated: 2024/05/31 12:50:27 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_substr(const char *s, unsigned int start, size_t len)
// {
// 	char	*sub;
// 	size_t	i;

// 	i = 0;
// 	if (!s)
// 		return (NULL);
// 	if (start > ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (len > ft_strlen(s + start))
// 		len = ft_strlen(s + start);
// 	sub = ft_calloc(len + 1, sizeof(char));
// 	if (!sub)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		sub[i] = s[start + i];
// 		i++;
// 	}
// 	sub[i] = '\0';
// 	return (sub);
// }

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	if (len > s_len)
		len = s_len;
	if (start >= s_len)
	{
		substr = (char *)malloc(1);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	substr = (char *)malloc(len + 1);
	if (substr == NULL)
		return (NULL);
	while (i++ < start)
		s++;
	ft_strlcpy(substr, s, len + 1);
	return (substr);
}
