/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/05 18:10:54 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*g_mini = NULL;

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	(void)argc;
	(void)argv;
	mini = malloc(sizeof(t_mini));
	if (!mini)
	{
		perror("Failed to allocate t_mini structure");
		exit(EXIT_FAILURE);
	}

	g_mini = mini;
	initialize_envp(envp);
	init_mini(mini);

	setup_signal_handlers();
	//--------------TESTING----------------
	// test_exec();
	// test_heredoc();
	// libft_extra_tester();
	//--------------!TESTING----------------
	// printf("%s\n", MINISHELL_ASCII);
	prompt_loop();
	// char *str = get_next_line(0);
	// printf("%s\n", str);
	// free(str);
	free_mini(&g_mini);
	return (EXIT_SUCCESS);
}
