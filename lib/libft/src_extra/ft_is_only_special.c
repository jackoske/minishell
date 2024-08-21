/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_special.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:33:28 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/21 17:55:43 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_is_only_special(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_is_special_symbol(str[i]))
			return (0);
	}
	return (1);
}

int	ft_is_special_in_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (ft_is_special_symbol(str[i]))
			return (1);
	}
	return (0);
}
