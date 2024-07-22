/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jskehan <jskehan@student.42Berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:19:41 by Jskehan           #+#    #+#             */
/*   Updated: 2024/07/22 15:24:15 by Jskehan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test_echo(t_mini *mini)
{
    char *full_command[] = {"echo", "Hello, world!", NULL};

    t_cmd cmd = {.full_command = full_command,
                 .command_path = "/bin/echo", // Not used for built-in commands
                 .fd_in = 0,  // stdin
                 .fd_out = 1, // stdout
                 .is_heredoc = 0,
                 .is_append = 0,
                 .is_outfile = 0,
                 .mini = mini}; // Add mini pointer

    t_list node = {.content = &cmd, .next = NULL};

    check_to_fork(mini, &node, NULL);
    printf("Exit status for echo: %d\n", mini->exit_status);
}

// Function to test pwd command
void test_pwd(t_mini *mini)
{
    char *full_command[] = {"pwd", NULL};

    t_cmd cmd = {.full_command = full_command,
                 .command_path = "/bin/pwd", // Not used for built-in commands
                 .fd_in = 0,  // stdin
                 .fd_out = 1, // stdout
                 .is_heredoc = 0,
                 .is_append = 0,
                 .is_outfile = 0,
                 .mini = mini}; // Add mini pointer

    t_list node = {.content = &cmd, .next = NULL};

    check_to_fork(mini, &node, NULL);
    printf("Exit status for pwd: %d\n", mini->exit_status);
}

void test_exec()
{
    // Hardcoded command
    char *full_command[] = {"/bin/ls", NULL};

    t_cmd cmd = {.full_command = full_command,
                 .command_path = "/bin/ls",
                 .fd_in = 0,  // stdin
                 .fd_out = 1, // stdout
                 .is_heredoc = 0,
                 .is_append = 0,
                 .is_outfile = 0,
                 .mini = NULL}; // Will set mini later

    // Wrap command in a list node
    t_list node = {.content = &cmd, .next = NULL};

    // Mini shell structure
    t_mini mini = {.envp = NULL, // Environment variables (could be set up if needed)
                   .node = &node,
                   .current_dir = NULL, // Current directory (could be set up if needed)
                   .exit_status = 0};

    // Set mini pointer in cmd
    cmd.mini = &mini;

    // Test the function
    test_echo(&mini);
    test_pwd(&mini);
    check_to_fork(&mini, &node, NULL);
    printf("Exit status: %d\n", mini.exit_status);
}

void test_heredoc(void)
{
    t_mini mini;
    char *warn = "Warning: unexpected EOF";

    mini.exit_status = 0;
    const char *limit = "pi"; // specify your delimiter here
    int fd = get_here_doc(&mini, limit, warn);
    if (fd != -1)
    {
        char buffer[1024];
        ssize_t nbytes = read(fd, buffer, sizeof(buffer) - 1);
        if (nbytes >= 0)
        {
            buffer[nbytes] = '\0';
            printf("Here-doc content:\n%s", buffer);
        }
        else
        {
            perror("read");
        }
        close(fd);
    }
    else
    {
        printf("Here-doc failed\n");
    }
}
