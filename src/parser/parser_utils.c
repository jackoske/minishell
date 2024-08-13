/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:38:35 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/13 12:43:10 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	w_count_quotes(char *input)
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

int	count_unescaped_quotes(char const *s1)
{
	int	count;
	int	i;
	int	d_quote;
	int	s_quote;

	i = 0;
	count = 0;
	d_quote = 0;
	s_quote = 0;
	while (s1 && s1[i])
	{
		s_quote = (s_quote + (!d_quote && s1[i] == '\'')) % 2;
		d_quote = (d_quote + (!s_quote && s1[i] == '\"')) % 2;
		if ((s1[i] == '\"' && !s_quote) || (s1[i] == '\'' && !d_quote))
			count++;
		i++;
	}
	if (s_quote || d_quote)
		return (-1);
	return (count);
}

char	*ft_trimm_quotes(char const *s1, int s_quote, int d_quote)
{
	int		unescaped_quotes;
	char	*trimmed;
	int		i;

	i = -1;
	unescaped_quotes = count_unescaped_quotes(s1);
	if (!s1 || unescaped_quotes == -1)
		return (NULL);
	trimmed = ft_calloc(ft_strlen(s1) - unescaped_quotes + 1, sizeof(char));
	if (!trimmed)
		return (NULL);
	while (*s1)
	{
		s_quote = (s_quote + (!d_quote && *s1 == '\'')) % 2;
		d_quote = (d_quote + (!s_quote && *s1 == '\"')) % 2;
		if ((*s1 != '\"' || s_quote) && (*s1 != '\'' || d_quote) && ++i >= 0)
			trimmed[i] = *s1;
		s1++;
	}
	trimmed[++i] = '\0';
	return (trimmed);
}

char	**ft_remove_quotes(char **tokenizedInput)
{
	char	**temp;
	char	*aux;
	int		i;

	i = -1;
	temp = ft_duplicate_2d_array(tokenizedInput);
	while (temp && temp[++i])
	{
		aux = ft_trimm_quotes(temp[i], 0, 0);
		free(temp[i]);
		temp[i] = aux;
	}
	return (temp);
}
