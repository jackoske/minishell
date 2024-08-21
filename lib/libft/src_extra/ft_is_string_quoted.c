/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_string_quoted.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:10:27 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/21 17:47:00 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_string_quoted(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len \
			- 1] == '\"'))
		return (1);
	return (0);
}
