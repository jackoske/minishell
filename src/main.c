/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/28 14:52:48 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void init_envp(char **envp, t_mini **mini)
{
	*mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		exit(EXIT_FAILURE);
	(*mini)->envp = envp;
	(*mini)->node = NULL;
	(*mini)->current_dir = getcwd(NULL, 0);
	(*mini)->exit_status = 0;
}

int main(int argc, char **argv, char **envp)
{
	t_mini *mini;
	(void)argc;
	(void)argv;
	// (void)envp;

	init_envp(envp, &mini);
	setup_signal_handlers();
	prompt_loop(mini);
	// libft_extra_tester();
	// char *str = get_next_line(0);
	// printf("%s\n", str);
	// free(str);
	free(mini);
	return (EXIT_SUCCESS);
}
