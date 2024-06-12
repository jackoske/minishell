/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:11:41 by iverniho          #+#    #+#             */
/*   Updated: 2024/06/12 18:40:47 by iverniho         ###   ########.fr       */
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

typedef struct s_node
{
	char			**full_command;
	char			*command_path;
	int				fd_in;
	int				fd_out;
	int				is_heredoc;
	int				is_append;
}					t_node;

typedef struct s_mini
{
	char			**envp;
	t_list			*node;
	char			*current_dir;
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
t_node				*set_redir(t_node *node, char *input, char **full_command, int *i);
t_node				*init_node(void);

#endif
