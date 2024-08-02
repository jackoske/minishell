/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/08/02 17:59:05 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*g_mini = NULL;

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;

	(void)argc;
	(void)argv;
	initialize_envp(&mini, envp);
	init_mini(mini);
	g_mini = mini;

	setup_signal_handlers();
	//--------------TESTING----------------
	// test_exec();
	// test_heredoc();
	// libft_extra_tester();
	//--------------!TESTING----------------
	// printf("%s\n", MINISHELL_ASCII);
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
