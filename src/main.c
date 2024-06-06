/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/06 18:03:12 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envp(char **envp, t_mini **mini)
{
	*mini = (t_mini *)malloc(sizeof(t_mini));
	if (!mini)
		exit(EXIT_FAILURE);
	(*mini)->envp = envp;
	(*mini)->token = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	*mini;
	(void)argc;
	(void)argv;
	// (void)envp;
	
	init_envp(envp, &mini);
	// prompt_loop(mini);
	libft_extra_tester();
	// char *str = get_next_line(0);
	// printf("%s\n", str);
	// free(str);
	free(mini);
	return (EXIT_SUCCESS);
}
