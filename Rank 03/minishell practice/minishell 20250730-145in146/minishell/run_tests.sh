#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

MINISHELL_EXECUTABLE="./minishell"
MINISHELL_OUTPUT="minishell_output.txt"
BASH_OUTPUT="bash_output.txt"
LOG_FILE="test_log.txt"

# Hardcoded command string for reliability
cmd_string="export MY_VAR=is_set; env | grep MY_VAR; unset MY_VAR; env | grep MY_VAR; ls /no/such/dir; echo $?; ls / > /dev/null; echo $?"

echo "---"
echo "Testing command string: $cmd_string" | tee $LOG_FILE

# Execute in bash
(eval "$cmd_string") > $BASH_OUTPUT 2>&1
BASH_EXIT_CODE=$?

# Execute in minishell
$MINISHELL_EXECUTABLE -c "$cmd_string" > $MINISHELL_OUTPUT 2>&1
MINISHELL_EXIT_CODE=$?

# Compare the outputs
if diff -u $BASH_OUTPUT $MINISHELL_OUTPUT >> $LOG_FILE; then
    echo -e "${GREEN}PASS: Command output matches bash.${NC}"
else
    echo -e "${RED}FAIL: Command output differs from bash.${NC}"
    echo "See diff in $LOG_FILE"
fi

# Compare exit codes
if [ "$BASH_EXIT_CODE" -eq "$MINISHELL_EXIT_CODE" ]; then
     echo -e "${GREEN}PASS: Exit codes match (Bash: $BASH_EXIT_CODE, Minishell: $MINISHELL_EXIT_CODE).${NC}"
else
     echo -e "${RED}FAIL: Exit codes differ (Bash: $BASH_EXIT_CODE, Minishell: $MINISHELL_EXIT_CODE).${NC}"
fi

echo "---"
echo "Testing finished. Check $LOG_FILE for details."
