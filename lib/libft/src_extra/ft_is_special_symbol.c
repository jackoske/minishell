/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_special_symbol.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:35:34 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/07 19:45:41 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_is_special_symbol(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_special_char_export(char c)
{
	char *prohibited_chars;

	prohibited_chars = "!@#$%^&*()-+=|\\{}[]:;\"'<>,.?/";
	while (*prohibited_chars) {
		if (c == *prohibited_chars) {
			return 1;
		}
		prohibited_chars++;
	}
	return 0;
}
