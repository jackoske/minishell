/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/30 11:38:41 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envp(char **envp, t_command **command)
{
	(*command) = malloc(sizeof(t_command));
	if (!command)
		exit(EXIT_FAILURE);
	(*command)->envp = envp;
	(*command)->cmnds = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*command;
	(void)argc;
	(void)argv;
	command = NULL;
	init_envp(envp, &command);
	prompt_loop(&command);
	ft_atoi("321");//testing import of library
	get_next_line(0);//testing import of library
	return (EXIT_SUCCESS);
}
