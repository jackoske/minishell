/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/26 17:25:17 by Jskehan          ###   ########.fr       */
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
	printf("%s\n", MINISHELL_ASCII);
	prompt_loop(mini);
	for (int i = 0; mini->envp[i]; i++)
		free(mini->envp[i]);
	free(mini->envp);
	free(mini);
	return (EXIT_SUCCESS);
}
