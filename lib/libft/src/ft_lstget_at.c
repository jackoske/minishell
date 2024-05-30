/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 09:01:49 by aperez-b          #+#    #+#             */
/*   Updated: 2024/05/29 18:08:14 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstget_at(t_list *lst, int i)
{
	t_list	*target;
	int		j;

	j = 0;
	if (!lst)
		return (NULL);
	while (lst && j++ < i)
		lst = lst->next;
	target = lst;
	return (target);
}
