/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:21:32 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/06 12:22:10 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (ptr == NULL)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(size);
	if (new_ptr != NULL)
	{
		if (size < sizeof(ptr))
			copy_size = size;
		else
			copy_size = sizeof(ptr);
		ft_memcpy(new_ptr, ptr, copy_size);
		free(ptr);
	}
	return (new_ptr);
}
