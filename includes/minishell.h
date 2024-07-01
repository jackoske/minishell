/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:11:41 by iverniho          #+#    #+#             */
/*   Updated: 2024/07/01 18:35:03 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "../lib/gnl/get_next_line.h"
#include "../lib/libft/includes/libft.h"
#include <dirent.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PROMPT "minishell> "
#define NEWLINE_ERR "minishell> syntax error near unexpected token `newline'"
#define SYNTAX_ERR "minishell> syntax error near unexpected token "
#define NO_FILE_ERR "minishell> No such file or directory: "
#define CMD_NOT_FOUND "minishell> command not found: "
#define PERM_ERR "minishell> permission denied: "

#define READ_END 0
#define WRITE_END 1

extern volatile sig_atomic_t g_sigint_received;

typedef struct s_cmd
{
	char **full_command;
	char *command_path;
	int fd_in;
	int fd_out;
	int is_heredoc;
	int is_append;
	int is_outfile;
	int exit_status;
} t_cmd;

typedef struct s_mini
{
	char **envp;
	t_list *node;
	char *current_dir;
	int exit_status;
} t_mini;

void prompt_loop(t_mini *mini);
int quotes_closed(char *line);
void libft_extra_tester(void);
int ft_word_count_quotes(char *input);
char *find_var(char *var, t_mini **mini);
char **find_env_var_and_replace(char *var, t_mini **mini, char **tokenizedInput);
char **expand_vars(char **tokenizedInput, t_mini **mini);
char **ft_remove_quotes(char **tokenizedInput);
char		**tokenize_special_symbols(const char *str, int i, int token_count);
char **tokenize_input(char *input, t_mini **mini);
char **split_by_spaces(char *input, int w_count);
char **populateTokenArray(char **tokenizedInput, char *input);
int ft_alloc_len(char const *s1);
t_cmd *set_redir(t_cmd *node, char *input, char **full_command, int *i);
t_cmd *init_cmd(void);

void *mini_perror(char *str, char *str2, int fd);
int get_here_doc(t_mini *mini, char *warn);
void ft_error(int error, char *arg);
void handle_sigint(int sig);
void setup_signal_handlers(void);
void setup_signal_handlers();

#endif
