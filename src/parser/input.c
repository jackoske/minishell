/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:20:49 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/12 17:19:23 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_tokenized_input(char **tokenized_input)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	j = 0;
	while (tokenized_input && tokenized_input[++i])
	{
		len = ft_strlen(tokenized_input[i]) - 1;
		if (j == 1 && is_special_char_input(tokenized_input[i][len]) == 1
			&& is_string_quoted(tokenized_input[i]) != 1)
			return (ft_error(6, tokenized_input[i]), 0);
		j = is_special_char_input(tokenized_input[i][len]);
		if (tokenized_input[i][0] == '|')
			j = 0;
	}
	return (1);
}

void	handle_input(char *input)
{
	char	**tokenized_input;
	t_list	*commands;

	tokenized_input = tokenize_input(input);
	if (!tokenized_input || !tokenized_input[0]
		|| !check_tokenized_input(tokenized_input))
	{
		free(input);
		if (tokenized_input)
			ft_free_2d_array(&tokenized_input);
		return ;
	}
	commands = create_nodes(tokenized_input);
	if (commands)
	{
		check_to_fork(commands);
		ft_lstclear(&commands, free_cmd);
	}
	ft_free_2d_array(&tokenized_input);
	free(input);
}
