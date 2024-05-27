/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:11:41 by iverniho          #+#    #+#             */
/*   Updated: 2024/05/27 09:58:06 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"

# define PROMPT "minishell> "

typedef enum e_types
{
	string = 1,
	quote = 2,
	red_in = 3,
	red_out = 4,
	append = 5,
	heredoc = 6,
	path = 7,
	command = 8,
	builtin = 9,
	pipe_symb = 10,
}	t_types;

typedef struct s_token
{
	char			*content;
	char			*cmd;
	struct s_token	*next;
	struct s_token	*head;
	t_types			type;
}	t_token;



void	prompt_loop(void);
int		quotes_closed(char *line);

#endif
