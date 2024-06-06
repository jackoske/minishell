/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_2d_array_fd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:21:48 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/06 12:29:41 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int ft_print_2d_array_fd(char **array, int fd)
{
	int i;

	if (fd < 0)
		return (0);
	i = 0;
	while (array && array[i])
	{
		ft_putendl_fd(array[i], fd);
		i++;
	}
	return (i);
}
