#include "minishell.h"

// Implementation of echo command with '-n' option
void mini_echo(t_cmd *cmd)
{
    int i = 1;
    int newline = 1;

    if (cmd->full_command[i] && ft_strcmp(cmd->full_command[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (cmd->full_command[i])
    {
        ft_putstr_fd(cmd->full_command[i], 1);
        if (cmd->full_command[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", 1);
}

// Implementation of pwd command
void mini_pwd(void)
{
    char *pwd = getcwd(NULL, 0);
    if (pwd)
    {
        ft_putstr_fd(pwd, 1);
        ft_putstr_fd("\n", 1);
        free(pwd);
    }
    else
    {
        perror("getcwd");
    }
}

// Check if a command is a built-in command
int is_builtin(t_cmd *cmd)
{
    if (!cmd->full_command[0])
        return 0;
    const char *builtins[] = {"echo", "pwd", "cd", "export", "unset", "env", "exit"};
    size_t num_builtins = sizeof(builtins) / sizeof(builtins[0]);

    for (size_t i = 0; i < num_builtins; i++)
    {
        if (ft_strcmp(cmd->full_command[0], builtins[i]) == 0)
            return 1;
    }
    return 0;
}
// Execute built-in commands
void execute_builtin(t_mini *mini, t_cmd *cmd)
{
    if (ft_strcmp(cmd->full_command[0], "echo") == 0)
        mini_echo(cmd);
    else if (ft_strcmp(cmd->full_command[0], "pwd") == 0)
        mini_pwd();
    // Add other built-in command implementations here
    // ...
    // Update the exit status
    mini->exit_status = 0;
}

void child_builtin(t_mini *mini, t_list *command)
{
    t_cmd *cmd = (t_cmd *)command->content;

    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);

    if (is_builtin(cmd))
    {
        execute_builtin(mini, cmd);
        exit(mini->exit_status);
    }
    else if (cmd->full_command)
        execve(cmd->command_path, cmd->full_command, mini->envp);
}

static void *child_redir(t_list *command)
{
    t_cmd *cmd = (t_cmd *)command->content;

    if (cmd->fd_in != STDIN_FILENO)
    {
        if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
            return (mini_perror("DUPERR", NULL, 1));
        close(cmd->fd_in); // Close only after duplicating
    }
    if (cmd->fd_out != STDOUT_FILENO)
    {
        if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
            return (mini_perror("DUPERR", NULL, 1));
        close(cmd->fd_out); // Close only after duplicating
    }
    return ("");
}

void *child_process(t_mini *mini, t_list *command)
{
    t_cmd *cmd = (t_cmd *)command->content;

    child_redir(command);
    if (is_builtin(cmd))
    {
        execute_builtin(mini, cmd);
        exit(mini->exit_status);
    }
    if (cmd->command_path)
    {
        execve(cmd->command_path, cmd->full_command, mini->envp);
        perror("execve");
        exit(EXIT_FAILURE);
    }
    exit(mini->exit_status);
}

void exec_fork(t_mini *mini, t_list *command)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        mini_perror("FORKERR", NULL, 1);
    }
    else if (pid == 0)
    {
        child_process(mini, command);
    }
    else
    {
        waitpid(pid, &mini->exit_status, 0);
    }
}


void *check_to_fork(t_mini *mini, t_list *command)
{
    t_cmd *cmd = (t_cmd *)command->content;
    DIR *dir = NULL;

    if (cmd->full_command)
        dir = opendir(*cmd->full_command);
    if (cmd->fd_in == -1 || cmd->fd_out == -1)
        return (NULL);
    if ((cmd->command_path && access(cmd->command_path, X_OK) == 0) || is_builtin(cmd))
        exec_fork(mini, command);
    else if (!is_builtin(cmd) && ((cmd->command_path && !access(cmd->command_path, F_OK)) || dir))
        mini->exit_status = 126;
    else if (!is_builtin(cmd) && cmd->full_command)
        mini->exit_status = 127;
    if (dir)
        closedir(dir);
    return ("");
}
