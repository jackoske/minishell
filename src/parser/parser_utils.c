/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:38:35 by iverniho          #+#    #+#             */
/*   Updated: 2024/06/07 17:44:31 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_word_count_quotes(char *input)
{
	int		i;
	int		count;
	char	quote;

	quote = ((i = 0), (count = 0), 0);
	while (input[i])
	{
		if (ft_is_space(input[i]))
		{
			while (ft_is_space(input[i]))
				i++;
			if (!quote)
				count++;
		}
		else
		{
			if ((input[i] == '\"' || input[i] == '\'') && quote == input[i])
				quote = 0;
			else if ((input[i] == '\"' || input[i] == '\''))
				quote = input[i];
			i++;
		}
	}
	return (count + 1);
}

char	**ft_remove_quotes(char **tokenizedInput)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = -1;
	k = 0;
	while (tokenizedInput[++i])
	{
		j = -1;
		while (tokenizedInput[i][++j])
		{
			if (tokenizedInput[i][j] == '\"' || tokenizedInput[i][j] == '\'')
			{
				temp = ft_substr(tokenizedInput[i], 1, ft_strlen(tokenizedInput[i])
						- 2);
				free(tokenizedInput[i]);
				tokenizedInput[i] = ft_strdup(temp);
				free(temp);
			}
		}
	}
	return (tokenizedInput);
}
