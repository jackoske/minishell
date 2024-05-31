/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:21:10 by iverniho          #+#    #+#             */
/*   Updated: 2024/05/30 17:23:31 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_closed(char *line)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	while (line[++i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (line[i] != quote && quote == 0)
				quote = line[i];
			else if (line[i] == quote)
				quote = 0;
		}
	}
	if (quote != 0)
		return (0);
	return (1);
}
