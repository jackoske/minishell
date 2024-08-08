/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:51:47 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/08 14:54:38 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_double_quotes(char *str)
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
		if (str[i] != '\"')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	*get_var_value(char *var)
{
	char	*var_value;

	var_value = find_var(var);
	if (var_value)
		return (var_value);
	else
		return (NULL);
}

char	*copy_or_replace_token(char *token, char *var)
{
	char	*var_value;

	if (ft_strchr(token, '$') == NULL)
		return (ft_strdup(token));
	var_value = get_var_value(var);
	if (var_value)
		return (var_value);
	else
		return (free(var_value), (token));
}
