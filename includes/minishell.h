/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:11:41 by iverniho          #+#    #+#             */
/*   Updated: 2024/06/10 12:55:43 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/gnl/get_next_line.h"
# include "../lib/libft/includes/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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
}					t_types;

typedef struct s_token
{
	char			*content;
	char			*cmd;
	struct s_token	*next;
	t_types			type;
}					t_token;

typedef struct s_full_command
{
	char			*full_command;
	char			*command_path;
	int				fd_in;
	int				fd_out;
	int				is_heredoc;
	int				is_append;
}					t_full_command;

typedef struct s_mini
{
	char			**envp;
	t_token			*token;
	t_full_command	*full_command;
	int				exit_status;
}					t_mini;

void				prompt_loop(t_mini *mini);
int					quotes_closed(char *line);
void				libft_extra_tester(void);
int					ft_word_count_quotes(char *input);
char				*find_var(char *var, t_mini **mini);
char				**find_env_var_and_replace(char *var,
		t_mini **mini, char **tokenizedInput);
char				**expand_vars(char **tokenizedInput, t_mini **mini);
char				**ft_remove_quotes(char **tokenizedInput);
char				**tokenize_special_symbols(const char *str);
char				**tokenize_input(char *input, t_mini **mini);
char				**split_by_spaces(char *input, int w_count);
char				**populateTokenArray(char **tokenizedInput, char *input);
int					ft_alloc_len(char const *s1);

#endif
