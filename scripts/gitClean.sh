#!/bin/bash

# Check if an argument is provided
if [ -z "$1" ]; then
  echo "Error: Please provide a commit message argument."
  exit 1
fi

# Clean project using make fclean
make fclean

# Add all files to git staging area
git add .

# Commit with the provided argument as message
git commit -m "$1"

# Push to remote repository (replace 'origin' with your actual remote)
git push

# Informative message
echo "Cleaned project, added all files, committed with message: '$1', and pushed to remote."

