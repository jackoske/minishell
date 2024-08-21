/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:50:12 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/21 17:31:29 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str, char q)
{
	int		len;
	char	*result;
	int		j;
	int		i;

	len = ft_strlen(str);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	i = 0;
	while (i < len)
	{
		if (str[i] != q)
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	**manage_replaced(char **replaced, char **last_str)
{
	last_str = NULL;
	ft_free_2d_array(&last_str);
	last_str = replaced;
	replaced = NULL;
	ft_free_2d_array(&replaced);
	return (last_str);
}
