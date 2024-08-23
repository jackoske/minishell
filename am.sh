#!/bin/bash

make re
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=readline.supp ./minishell
