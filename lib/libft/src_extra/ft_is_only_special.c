/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_special.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:33:28 by iverniho          #+#    #+#             */
/*   Updated: 2024/06/07 17:34:35 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_is_only_special(char *str)
{
	int	 i;
	i = -1;
	while (str[++i])
	{
		if (!ft_is_special_symbol(str[i]))
			return (0);
	}
	return (1);
}
