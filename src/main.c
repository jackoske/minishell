/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/25 16:03:23 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	(void)argc;
	(void)argv;
	initialize_envp(&mini, envp);
	setup_signal_handlers();
	//--------------TESTING----------------
	// test_exec();
	// test_heredoc();
	// libft_extra_tester();
	//--------------!TESTING----------------
	printf("%s\n", MINISHELL_ASCII);
	prompt_loop(mini);
	// char *str = get_next_line(0);
	// printf("%s\n", str);
	// free(str);
	for (int i = 0; mini->envp[i]; i++)
		free(mini->envp[i]);
	free(mini->envp);
	free(mini);
	return (EXIT_SUCCESS);
}
