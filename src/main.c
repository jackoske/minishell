/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/06/05 20:05:39 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	init_envp(char **envp, t_command **command)
// {
// 	(*command) = malloc(sizeof(t_command));
// 	if (!command)
// 		exit(EXIT_FAILURE);
// 	(*command)->envp = envp;
// 	(*command)->token = NULL;
// }

int	main(int argc, char **argv, char **envp)
{
	t_command	*command;
	(void)argc;
	(void)argv;
	(void)envp;
	command = NULL;
	// init_envp(envp, &command);
	// prompt_loop(&command);
	libft_extra_tester();
	ft_atoi("321");//testing import of library
	return (EXIT_SUCCESS);
}
