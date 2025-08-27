#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void ft_puts(const char *s) {
    while (*s) {
        write(1, s++, 1);
    }
    write(1, "\n", 1);
}

int is_valid(char *s) {
    int count = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '(') {
            count++;
        } else if (s[i] == ')') {
            count--;
        }
        if (count < 0) {
            return 0;
        }
    }
    return count == 0;
}

int min_remove(char *s) {
    int open = 0;
    int close = 0;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '(') {
            open++;
        } else if (s[i] == ')') {
            if (open > 0) {
                open--;
            } else {
                close++;
            }
        }
    }
    return open + close;
}

void solve(char *s, int must_fix, int fixed, int pos) {
    if (fixed == must_fix) {
        if (is_valid(s)) {
            ft_puts(s);
        }
        return;
    }

    for (int i = pos; s[i]; i++) {
        if (s[i] == '(' || s[i] == ')') {
            char temp = s[i];
            s[i] = ' ';
            solve(s, must_fix, fixed + 1, i + 1);
            s[i] = temp;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    int to_remove = min_remove(argv[1]);
    solve(argv[1], to_remove, 0, 0);

    return 0;
}
