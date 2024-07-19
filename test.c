#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Change the current working directory to the path provided by the user
    if (chdir(argv[1]) != 0) {
        perror("chdir");
        return EXIT_FAILURE;
    }

    // Print the new current working directory
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory changed to: %s\n", cwd);
    } else {
        perror("getcwd");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
