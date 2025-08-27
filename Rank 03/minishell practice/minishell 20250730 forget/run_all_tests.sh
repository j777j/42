#!/bin/bash
# This is the final attempt at a reliable test script in bash.

# Comprehensive Test Suite for Minishell

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Log file
LOG_FILE="test_log.txt"
BASH_LOG="bash_output.txt"
MINISHELL_LOG="minishell_output.txt"

# Clean up previous main log file
rm -f $LOG_FILE

# Function to run a test case
run_test() {
    COMMAND=$1
    DESCRIPTION=$2

    rm -f $BASH_LOG $MINISHELL_LOG
    
    echo "---" >> $LOG_FILE
    echo "Test: $DESCRIPTION" >> $LOG_FILE
    echo "Command: $COMMAND" >> $LOG_FILE
    echo "---" >> $LOG_FILE

    # Run in bash
    echo "$COMMAND" | bash > "$BASH_LOG" 2>&1
    BASH_EXIT_CODE=$?

    # Run in minishell
    # The -c flag is used here, assuming it reads the command string correctly.
    ./minishell -c "$COMMAND" > "$MINISHELL_LOG" 2>&1
    MINISHELL_EXIT_CODE=$?

    # Compare outputs
    # Normalize line endings to avoid diff issues
    sed -i 's/\r$//' $BASH_LOG
    sed -i 's/\r$//' $MINISHELL_LOG
    
    DIFF_OUTPUT=$(diff -u $BASH_LOG $MINISHELL_LOG)
    DIFF_EXIT_CODE=$?

    if [ $DIFF_EXIT_CODE -eq 0 ] && [ $BASH_EXIT_CODE -eq $MINISHELL_EXIT_CODE ]; then
        echo -e "${GREEN}PASS:${NC} $DESCRIPTION"
    else
        echo -e "${RED}FAIL:${NC} $DESCRIPTION"
        echo "    Command: $COMMAND"
        echo "    Exit Codes: Bash ($BASH_EXIT_CODE), Minishell ($MINISHELL_EXIT_CODE)"
        echo "    --- DIFF ---"
        echo "$DIFF_OUTPUT"
        echo "    ------------"
    fi

    rm -f $BASH_LOG $MINISHELL_LOG
}

# --- Test Cases ---

echo "Running Comprehensive Tests..."

# 1. Simple Commands
run_test "echo 'hello simple command'" "Simple command: echo"
run_test "/bin/echo hello world" "Simple command with absolute path"

# 2. Pipes
run_test "echo 'a\nb\nc' | grep 'b'" "Pipe: echo | grep"
run_test "cat Makefile | grep 'all' | sort" "Pipe: cat | grep | sort"
run_test "echo 'a b c' | wc -w" "Pipe: echo | wc"

# 3. Redirections
rm -f outfile # Clean up before redirection tests
run_test "echo 'hello' > outfile" "Redirection: >"
run_test "cat < outfile" "Redirection: <"
run_test "grep 'hello' < outfile" "Redirection: < with command"
run_test "echo ' world' >> outfile" "Redirection: >>"
run_test "cat outfile" "Verify >> redirection"
run_test "rm outfile" "Cleanup outfile"

# 4. Built-ins
run_test "echo 'testing echo'" "Built-in: echo"
run_test "pwd" "Built-in: pwd"
# The env test is tricky due to '_' variable. We will skip direct comparison for now.
# run_test "env | sort" "Built-in: env with pipe"

# 5. Variable Expansion
run_test "export TEST_VAR='hello'; echo \$TEST_VAR" "Variable expansion"
run_test "export TEST_VAR='hello again'; echo \"\$TEST_VAR\"" "Variable expansion with double quotes"
run_test "export TEST_VAR='wont show'; echo '\$TEST_VAR'" "Variable expansion with single quotes"
run_test "unset TEST_VAR; echo \$TEST_VAR" "Unset variable"

echo "Comprehensive tests finished."
echo "Check test_log.txt for a detailed log."
