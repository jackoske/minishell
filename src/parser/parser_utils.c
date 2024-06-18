/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:38:35 by iverniho          #+#    #+#             */
/*   Updated: 2024/06/18 14:47:16 by iverniho         ###   ########.fr       */
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

int	ft_alloc_len(char const *s1)
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

static char	*ft_trimm_quotes(char const *s1, int s_quote, int d_quote)
{
	int		count;
	char	*trimmed;
	int 	i;

	i = -1;
	count = ft_alloc_len(s1);
	if (!s1 || count == -1)
		return (NULL);
	trimmed = ft_calloc(ft_strlen(s1) - count + 1, sizeof(char));
	if (!trimmed)
		return (NULL);
	while (*s1)
	{
		s_quote = (s_quote + (!d_quote && *s1 == '\'')) % 2;
		d_quote = (d_quote + (!s_quote && *s1 == '\"')) % 2;
		if ((*s1 != '\"' || s_quote) && (*s1 != '\'' || d_quote) \
			&& ++i >= 0)
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
	// i = -1;
	// while (temp && temp[++i])
	// {
	// 	if (ft_is_special_in_str(temp[i]) && ft_is_special_in_str(temp[i++]))
	// 		return (NULL);

	// }
	return (temp);
}

t_node	*init_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->full_command = NULL;
	node->command_path = NULL;
	node->fd_in = 0;
	node->fd_out = 1;
	node->is_heredoc = 0;
	node->is_append = 0;
	return (node);
}
