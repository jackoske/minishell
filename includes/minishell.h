/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 15:11:41 by iverniho          #+#    #+#             */
/*   Updated: 2024/08/13 14:34:45 by Jskehan          ###   ########.fr       */
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
# define CMD_NOT_FOUND ": command not found"
# define PERM_ERR "minishell> permission denied: "
# define NUM_REQ "numeric argument required"
# define NOT_VALID_ID " not a valid identifier"
# define CD_ERR "minishell: cd: HOME not set"

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

typedef struct param
{
	int							token_count;
	int							i;
}								t_param;

typedef struct s_error_info
{
	int							error_code;
	const char					*message;
	void						(*action)(int exit_code, char *arg,
								const char *message);
}								t_error_info;

typedef struct s_signals
{
	volatile sig_atomic_t		sigint_received;
	volatile sig_atomic_t		is_executing_command;
}								t_signals;

typedef struct s_mini
{
	char						**envp;
	t_list						*node;
	char						*current_dir;
	int							exit_status;
	t_signals					signals;
}								t_mini;

extern t_mini					*g_mini;

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
t_cmd							*init_cmd(void);
void							init_mini(t_mini *mini);
void							free_mini(t_mini **mini);
void							init_envp(char **envp);
void							free_cmd(void *cmd_ptr);
void							handle_input(char *input);
t_list							*create_nodes(char **input);
void							setup_signal_handlers(void);
void							setup_child_signals(void);
void							handle_sigint(int sig);
void							initialize_envp(char **envp);

/* Error Handling */
void							*mini_perror(char *str, char *str2, int fd);
void							ft_error(int error_code, char *arg);
void							ft_error_with_exit(int error_code, char *arg,
									int exit_code, char *message);
/* Input Handling and Parsing */
char							**tokenize_input(char *input);
char							**tokenize_special_symbols(const char *str,
									int i, int token_count);
char							**split_spaces(char *input, int w_count);
char							**populate_token_array(char **tokenizedInput,
									char *input);
int								w_count_quotes(char *input);
int								quotes_closed(char *line);
int								ft_alloc_len(char const *s1);
char							*ft_trimm_quotes(char const *s1, int s_quote,
									int d_quote);
void							allocate_and_copy_token1(char **tokens,
									int token_count, const char *str, int c[5]);
void							allocate_and_copy_token2(char **tokens,
									int token_count, const char *str, int n[5]);
void							imp_while(int *i, int len, const char *str,
									int *start);
char							**ft_add_row_2d_array1(char **array, char *row);
void							add_special_row(char ***tempTokenArray,
									char *specialSymbolArray, int *i);
char							**split_spaces(char *input, int w_count);
void							define_symbol_len(int *len, char index1,
									char index2);
int								is_special_char_input(char c);
int								is_string_quoted(char *str);

/* Variable Expansion and Environment Handling */
char							*find_var(char *var);
char							**find_env_var_and_replace(char *var,
									char **tokenizedInput);
char							**expand_vars(char **tokenizedInput);
char							**ft_remove_quotes(char **tokenizedInput);
char							*remove_double_quotes(char *str);
char							**manage_replaced(char **replaced,
									char **last_str);

/* Command Handling */
void							*check_to_fork(t_list *command);
t_cmd							*set_redir(t_cmd *node, char *input,
									char **full_command, int *i);
char							*resolve_command_path(char *command);
int								is_builtin(t_cmd *cmd);
void							execute_builtin(t_cmd *cmd);
int								check_after_equal(char *str);
int								add_env_key(char *str, int len);
int								is_special_char_in_env(char *str);
void							replace_value(char *key, char *value);
int								is_already_exist(char *key);
void							show_last_command_status(char **str);
int								is_special_char_export(char c);
int								is_all_num(char *str);
int								is_string_quoted(char *str);

/* Built-in Commands */
void							copy_envp(t_mini *mini, char ***new_envp_array,
									char *new_env);
int								handle_edge_cases(char **args);
int								mini_cd(char **args);
void							mini_echo(t_cmd *cmd);
void							mini_pwd(void);
void							mini_exit(char **args);
void							mini_export(char **args);
void							mini_env(void);
void							mini_unset(char **args);

/* Execution and Testing */
void							prompt_loop(void);
int								get_here_doc(const char *limit,
									const char *warn);
void							libft_extra_tester(void);
void							print_nodes(t_list *node);
void							test_exec(void);
void							test_heredoc(void);
void							debug_print_command_parts(t_cmd *cmd);
void							debug_tokenized_input(char **tokenized_input);

char							*ft_getenv(const char *name, char **envp,
									int len);
int								get_fd(int oldfd, t_cmd *cmd, char *path,
									int mode);
char							**ft_setenv(const char *name, const char *value,
									char **envp, int overwrite);
char							**copy_env(char **envp);

/// temporary

int								check_special_in_key(char *str);

void							child_redir(t_cmd *cmd);

void							child_process(t_cmd *cmd);

void							create_pipes(int num_cmds, int pipes[][2]);

void							close_pipes_in_parent(int num_cmds,
									int pipes[][2]);

void							exec_pipes(t_list *commands);

#endif // MINISHELL_H
