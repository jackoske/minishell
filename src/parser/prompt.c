/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/07 17:52:37 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_prompt(void)
{
	printf("%s", PROMPT);
	rl_on_new_line();
}

static int	check_command(char *input)
{
	if (!quotes_closed(input))
		return (printf("Syntax error\n"), 0);
	return (1);
}

static char	*read_command(void)
{
	char	*input;

	input = readline("");
	if (!check_command(input))
		return (NULL);
	if (input != NULL)
		add_history(input);
	return (input);
}

void	prompt_loop(t_mini *mini)
{
	char	*input;
	char	**tokenizedInput;
	int		i;

	tokenizedInput = NULL;
	while (1)
	{
		print_prompt();
		input = read_command();
		if (input == NULL || input[0] == '\0')
		{
			free(input);
			continue ;
		}
		tokenizedInput = ft_remove_quotes(tokenize_input(input, &mini));
		i = -1;
		while (tokenizedInput && tokenizedInput[++i])
			printf("tokenizedInput very last step: %s\n", tokenizedInput[i]);
		free(input);
	}
}
