/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:09:11 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/21 15:47:45 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_prompt(void)
{
	printf("%s", PROMPT);
	rl_on_new_line();
}

static char	*read_command(void)
{
	char	*input;

	input = readline("");
	if (input != NULL)
	{
		add_history(input);
		printf("Command entered: %s\n", input);
	}
	return (input);
}

void	prompt_loop(void)
{
	char *input;

	while (1)
	{
		print_prompt();
		input = read_command();
		if (input == NULL)
		{
			break ;
		}
		free(input);
	}
}
