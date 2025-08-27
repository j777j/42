# Minishell Project Analysis & Plan

## Project Overview
This project is a simple UNIX shell, `minishell`, written in C. It involves parsing user input, handling commands, pipes, redirections, and built-in shell functions.

## User-Defined Rules
- **Reply in Chinese.**
- **Adhere to the 42 school norm:**
    - No more than 25 lines per function.
    - No more than 5 functions per `.c` file.
    - Other standard 42 coding conventions.

---
## Current Status (As of July 25, 2025)

This document reflects the state of the project after a significant refactoring and bug-fixing session.

### Core Components Status
- **Lexer (`src/lexer.c`):**
    - **Implemented:** Tokenization for words, operators (`|`, `>`, `>>`, `<`, `<<`), quoted strings, and environment variable expansion (`$VAR`, `$?`).
    - **Fixed (July 25):** Added robust error handling for unclosed quotes. The lexer now correctly reports a syntax error instead of failing silently.

- **Parser (`src/parser.c`):**
    - **Implemented:** A recursive descent parser that builds an Abstract Syntax Tree (AST). It correctly handles pipes, all redirection types (including heredoc `<<`), and command arguments.
    - **Improved (July 25):** Enhanced syntax error reporting to be more specific, indicating the token that caused the error.

- **Executor (`src/executor.c`):**
    - **Implemented:** An AST traversal mechanism to execute commands. It handles external commands, pipes, and all redirections.
    - **Fixed (July 25):** Major architectural flaw in built-in command handling has been resolved. `cd`, `exit`, `export`, and `unset` now correctly run in the parent shell process, allowing them to modify the shell's state as intended. This fix also applies to built-ins combined with redirections (e.g., `export VAR=1 > /dev/null`).
    - **Improved (July 25):** The `wait` logic in `execute_pipe_cmd` has been made robust. It now correctly waits for the specific child processes and sets the shell's exit status (`$?`) to that of the rightmost command in a pipeline.

- **Built-ins (`src/builtins/`):**
    - **Implemented and Verified:** `echo`, `pwd`, `env`, `cd`, `exit`, `export`, and `unset` are all fully implemented and functional. The previous issue where some were ineffective has been resolved by the executor fix.

- **Heredoc (`<<`):**
    - **Implemented and Verified:** Full support for heredoc is present in the lexer, parser, and executor.

### Summary of Recent Changes (July 25, 2025)
- **Fixed Parent Built-in Execution:** Correctly execute `cd`, `export`, `unset`, `exit` in the main process, even with redirections.
- **Fixed Unclosed Quote Errors:** The lexer now detects and reports errors for unclosed quotes.
- **Fixed Pipe Exit Status:** The exit status (`$?`) of a pipeline is now correctly set to the status of the last command.
- **Improved Syntax Error Messages:** Parser errors are now more specific.
- **Code Verification:** Confirmed that `export`, `unset`, heredoc, and variable expansion were already implemented, contrary to previous plans.

## Action Plan
The most critical bugs have been addressed. The remaining tasks are focused on final testing, edge cases, and cleanup.

1.  **Comprehensive Testing:**
    - Test various combinations of pipes, redirections, and built-ins.
    - Test edge cases for `export` and `unset` (e.g., invalid identifiers, empty values).
    - Test heredoc with various delimiters and content.
    - Test variable expansion in different contexts (e.g., `echo "$VAR"`, `echo $VAR`, `echo '$VAR'`).
2.  **Final Cleanup:**
    - Review the entire codebase for potential memory leaks.
    - Ensure all code adheres to the 42 school norm.
    - Check for any remaining minor bugs or inconsistencies.
3.  **Submit the project.**
