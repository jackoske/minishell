/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:09:06 by Jskehan           #+#    #+#             */
/*   Updated: 2024/05/22 17:55:16 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	prompt_loop();
	ft_atoi("321");//testing import of library
	get_next_line(0);//testing import of library
	return (EXIT_SUCCESS);
}
