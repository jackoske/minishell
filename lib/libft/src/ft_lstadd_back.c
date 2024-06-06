/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jskehan <jskehan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 23:45:32 by jskehan           #+#    #+#             */
/*   Updated: 2023/11/22 22:46:14 by jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst && new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		ft_lstlast(*lst)->next = new;
	}
}
