/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 17:14:53 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/09 16:23:23 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		count++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c)
			i++;
	}
	return (count);
}

static int	letter_count(char const *s, char c, int index)
{
	int		count;

	count = 0;
	while (s[index] != c && s[index] != '\0')
	{
		count++;
		index++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	tab = ((i = 0), (k = 0), malloc(sizeof(char *) * (word_count(s, c) + 1)));
	if (!s || !c || !tab)
		return (NULL);
	while (s[k] == c)
		k++;
	while (s[k] != '\0')
	{
		j = 0;
		tab[i] = malloc(sizeof(char) * letter_count(s, c, k) + 1);
		if (!tab[i])
			return (NULL);
		while (s[k] != c && s[k] != '\0')
			tab[i][j++] = s[k++];
		tab[i][j] = '\0';
		while (s[k] == c)
			k++;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
