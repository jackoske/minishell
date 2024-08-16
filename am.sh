#!/bin/bash

# Run make re
make re

# Check if make re was successful
if [ $? -eq 0 ]; then
	echo "make re successful"
	
	# Run minishell
	./minishell
else
	echo "make re failed"
fi
