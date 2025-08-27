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
## Current Status (As of July 28, 2025)

The project is in the final bug-fixing stage. After major refactoring of the parser and executor, we have addressed issues with redirection, command argument parsing, and execution error codes. The `minishell_tester` now passes **139 out of 146** tests.

### Core Components Status
- **Parser (`src/parser.c`):** Stable.
- **Executor (`src/executor.c`):** Stable.
- **Built-ins (`src/builtins/`):** `exit` and `cd` argument handling fixed.
- **Error Handling (`executor.c`, `executor_utils.c`):** Correct error codes for permission/directory issues are now returned.
- **Expander (`src/expander.c`):**
    - **In Progress:** A new `expander.c` module has been created to handle all parameter expansion logic.
    - **Setback (July 28):** An attempt to incrementally fix expansion logic using the `replace` tool resulted in a corrupted file and major compilation errors due to improper handling of special characters in the tool's input.

### Summary of Recent Changes (July 28, 2025)
- **Fixed `exit` and `cd` built-ins.**
- **Fixed Execution Error Codes.**
- **Test Progress:** Reached **139/146** before the expander corruption.

## Remaining Issues & Action Plan

All 7 remaining failures are related to **parameter expansion and word splitting**.

1.  **`$` Character Expansion** (Tests 17, 19): `echo "$"` or `echo $` fails to print a literal `$`.
2.  **`*` Wildcard Expansion** (Test 13): `echo "*"` incorrectly performs globbing inside quotes.
3.  **Empty/Unset Variable Expansion** (Tests 134, 135): `$EMPTY` and `$EMPTY echo hi` are not handled correctly.
4.  **Word Splitting** (Test 39): `cd $PWD` fails because the expanded path is not split into multiple arguments.
5.  **Variable as Command** (Test 133): `$PWD` as a command fails with the wrong error code.

**Next Step:** Recover from the compilation failure by overwriting the corrupted `src/expander.c` with a complete, clean, and correct implementation. This new implementation will address:
-   Correct handling of single and double quotes.
-   Correct expansion of `$?`, `$VAR`, and literal `$` characters.
-   Safe memory management to prevent `double free` errors.
-   Initial logic for word splitting and handling of empty strings.

---
## Status Update (July 31, 2025)

After a major refactoring of the `lexer` and `expander` modules, the project now passes **140 out of 146** tests in the official `minishell_tester`. The core parameter expansion logic is now correct.

### Remaining Issues (6 failures)
1.  **Quoted Filenames in Redirections (Tests 86, 87, 88):** Commands like `ls > "./outfile with spaces"` fail with "No such file or directory". This is because the parser passes the filename with quotes to the executor, which then tries to open a file with literal quotes in its name.
2.  **Empty Variable Expansion (Tests 134, 135):** Commands like `$EMPTY` or `$EMPTY echo hi` (where `EMPTY` is unset) cause a "command not found" error, whereas bash treats them as no-ops or executes the subsequent command.
3.  **Miscellaneous Failure (Test 13):** `echo "> >> < * ..."` fails despite having the same output as bash. This might be an issue with the tester itself.

### Action Plan
1.  **Fix Quoted Filename Redirections:** The highest priority is to fix the redirection issue. This will be done by expanding the filename string within the `apply_redirections` function in `executor.c` *before* calling `open()`. This ensures that quotes are removed and variables are expanded correctly.
2.  **Fix Empty Variable Handling:** Address the behavioral difference for unset variables. This will likely require modifying the `expander` to remove empty strings from the argument list after expansion, unless they were explicitly quoted (e.g., `echo ""`).
3.  **Investigate Test 13:** Defer until the other, more critical, bugs are fixed.

---
## Status Update (July 31, 2025 - Evening)

The redirection issue is now **fixed**. The project now passes **143 out of 146** tests.

### Remaining Issues (3 failures)
1.  **Empty Variable Expansion (Tests 134, 135):** Unchanged. This is the next priority.
2.  **`echo` Spacing (Test 13):** `echo "> >> < * ..."` has an extra space in its output. This is likely a minor issue in `ft_split` or the expander's word splitting logic.
3.  **Warnings:** The tester shows `✅⚠️` for most tests, indicating a minor discrepancy in error messages (our shell adds an "exit" message). This is a low-priority cosmetic issue.

### Action Plan
1.  **Fix Empty Variable Handling:** Implement logic in `expander.c` to remove empty strings from the final argument list if they resulted from an unquoted variable expansion.
2.  **Fix `echo` Spacing:** Investigate and fix the extra space issue.
3.  **Review Warnings:** Address the "exit" message discrepancy if time permits.