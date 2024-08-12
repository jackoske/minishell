/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:00:36 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/09 17:01:16 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_quote_string(const char *str)
{
	char	*quoted_str;
	int		i;
	int		j;

	quoted_str = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	if (!quoted_str)
		return (NULL);
	i = 0;
	j = 0;
	quoted_str[i++] = '`';
	while (str[j])
		quoted_str[i++] = str[j++];
	quoted_str[i] = '\'';
	return (quoted_str);
}
