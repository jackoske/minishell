/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iverniho <iverniho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:11:41 by iverniho          #+#    #+#             */
/*   Updated: 2024/07/28 16:25:18 by iverniho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/gnl/get_next_line.h"
# include "../lib/libft/includes/libft.h"
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define PROMPT "minishell> "
# define NEWLINE_ERR "minishell> syntax error near unexpected token `newline'"
# define SYNTAX_ERR "minishell> syntax error near unexpected token "
# define NO_FILE_ERR "minishell> No such file or directory: "
# define CMD_NOT_FOUND "minishell> command not found: "
# define PERM_ERR "minishell> permission denied: "

# define READ_END 0
# define WRITE_END 1

extern volatile sig_atomic_t	g_sigint_received;
extern volatile sig_atomic_t	g_is_executing_command;

# define MINISHELL_ASCII \
	"\
 ______   ____  ____   ____   ___  __ __    ___  _      _\n\
|   |   ||    ||    \\ |    |/ ___/|  |  |  / __]| |    | |    \n\
| _   _ | |  | |  _  | |  |(   \\_ |  |  | /  [_ | |    | |    \n\
|  \\_/  | |  | |  |  | |  | \\__  ||  _  ||  ___]| |___ | |___ \n\
|   |   | |  | |  |  | |  | /  \\ ||  |  ||   [_ |     ||     |\n\
|   |   | |  | |  |  | |  | \\    ||  |  ||     ||     ||     |\n\
|_______||____||__|__||____| \\____|__|__||_____||_____||_____|\n\
 / ___/|  |  |   /  ]|  |/ ]/ ___/                            \n\
(   \\_ |  |  |  /  / |  ' /(   \\_                             \n\
 \\__  ||  |  | /  /  |    \\ \\__  |                            \n\
 /  \\ ||  :  |/   \\_ |     \\/  \\ |                            \n\
 \\    ||     |\\     ||  .  |\\    |                            \n\
  \\___| \\__,_| \\____||__|\\_| \\___|                     😻    \n\
"

/* ************************************************************************** */
/*                                                                            */
/* Struct Definitions                                                         */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_mini
{
	char						**envp;
	t_list						*node;
	char						*current_dir;
	int							exit_status;
}								t_mini;

typedef struct s_cmd
{
	char						**full_command;
	char						*command_path;
	int							fd_in;
	int							fd_out;
	int							is_heredoc;
	int							is_append;
	int							is_outfile;
	t_mini						*mini;
}								t_cmd;

/* ************************************************************************** */
/*                                                                            */
/* Function Prototypes                                                        */
/*                                                                            */
/* ************************************************************************** */

/* Initialization and Setup */
t_cmd							*init_cmd(t_mini *mini);
void							setup_signal_handlers(void);
void							setup_child_signals(void);
void							handle_sigint(int sig);
void							initialize_envp(t_mini **mini, char **envp);

/* Error Handling */
void							*mini_perror(char *str, char *str2, int fd);
void							ft_error(int error, char *arg);

/* Input Handling and Parsing */
char							**tokenize_input(char *input, t_mini **mini);
char							**tokenize_special_symbols(const char *str,
									int i, int token_count);
char							**split_by_spaces(char *input, int w_count);
char							**populateTokenArray(char **tokenizedInput,
									char *input);
int								ft_word_count_quotes(char *input);
int								quotes_closed(char *line);
int								ft_alloc_len(char const *s1);

/* Variable Expansion and Environment Handling */
char							*find_var(char *var, t_mini **mini);
char							**find_env_var_and_replace(char *var,
									t_mini **mini, char **tokenizedInput);
char							**expand_vars(char **tokenizedInput,
									t_mini **mini);
char							**ft_remove_quotes(char **tokenizedInput);

/* Command Handling */
void							*check_to_fork(t_mini *mini, t_list *command);
t_cmd							*set_redir(t_cmd *node, char *input,
									char **full_command, int *i);
char							*resolve_command_path(char *command,
									t_mini **mini);
int								is_builtin(t_cmd *cmd);
void							execute_builtin(t_mini *mini, t_cmd *cmd);
int								check_after_equal(char *str);
int								add_env_key(char *str, t_mini *mini, int len);
int								is_special_char_in_env(char *str);
void							replace_value(char *key, char *value, t_mini *mini);
int								is_already_exist(char *key, t_mini *mini);

/* Built-in Commands */
int								mini_cd(char **args, t_mini *mini);
void							mini_echo(t_cmd *cmd);
void							mini_pwd(void);
void							mini_exit(char **args, t_mini *mini);
void							mini_export(char **args, t_mini *mini);
void							mini_env(t_mini *mini);
void							mini_unset(char **args, t_mini *mini);

/* Execution and Testing */
void							prompt_loop(t_mini *mini);
int								get_here_doc(t_mini *mini, const char *limit,
									const char *warn);
void							libft_extra_tester(void);
void							print_nodes(t_list *node);
void							test_exec(void);
void							test_heredoc(void);
void							debug_print_command_parts(t_cmd *cmd);
void							debug_tokenized_input(char **tokenized_input);

char							*ft_getenv(const char *name, char **envp,
									int len);
char							**ft_setenv(const char *name, const char *value,
									char **envp, int overwrite);
char							**copy_env(char **envp);
#endif // MINISHELL_H
