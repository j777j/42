#!/bin/bash
source 42-philosophers-tester/test.sh

times_to_eat=10

mandatory_tests () {
    printf "${OBJ_COLOR}Mandatory tests${RESET}\n\n"
    die 1 800 200 200 $times_to_eat
    live 5 800 200 200 7
    live 4 410 200 200 $times_to_eat
    die 4 310 200 100 $times_to_eat
}

uneven_live () {
    printf "${OBJ_COLOR}Testing uneven numbers - they shouldn't die${RESET}\n\n"
    live 5 800 200 200 $times_to_eat
    live 5 610 200 200 $times_to_eat
    live 199 610 200 200 $times_to_eat
}

uneven_live_extended () {
    printf "${OBJ_COLOR}Testing uneven numbers (overkill) - they shouldn't die${RESET}\n\n"
    live 5 610 200 100 $times_to_eat
    live 5 601 200 200 $times_to_eat
    live 31 610 200 100 $times_to_eat
    live 31 610 200 200 $times_to_eat
    live 31 605 200 200 $times_to_eat
    live 31 601 200 200 $times_to_eat
    live 131 610 200 100 $times_to_eat
    live 131 610 200 200 $times_to_eat
    live 131 605 200 200 $times_to_eat
    live 131 601 200 200 $times_to_eat
    live 199 610 200 100 $times_to_eat
    live 199 610 200 200 $times_to_eat
    live 199 605 200 200 $times_to_eat
    live 199 601 200 200 $times_to_eat
}

even_live () {
    printf "${OBJ_COLOR}Testing even numbers - they shouldn't die${RESET}\n"
    live 4 410 200 100 $times_to_eat
    live 4 410 200 200 $times_to_eat
    live 198 610 200 200 $times_to_eat
    live 198 800 200 200 $times_to_eat
}

even_live_extended () {
    printf "${OBJ_COLOR}Testing even numbers (overkill) - they shouldn't die${RESET}\n"
    live 50 410 200 100 $times_to_eat
    live 50 410 200 200 $times_to_eat
    live 50 405 200 200 $times_to_eat
    live 50 401 200 200 $times_to_eat
    live 130 410 200 100 $times_to_eat
    live 130 410 200 200 $times_to_eat
    live 130 405 200 200 $times_to_eat
    live 130 401 200 200 $times_to_eat
    live 198 410 200 100 $times_to_eat
    live 198 410 200 200 $times_to_eat
    live 198 405 200 200 $times_to_eat
    live 198 401 200 200 $times_to_eat
}

even_die () {
    printf "${OBJ_COLOR}Testing even numbers - one should die${RESET}\n"
    die 3 599 200 200 $times_to_eat
    die 31 599 200 200 $times_to_eat
    die 131 596 200 200 $times_to_eat
}

even_die_extended () {
    printf "${OBJ_COLOR}Testing even numbers - one should die${RESET}\n"
    die 4 310 200 100 $times_to_eat
    die 50 396 200 200 $times_to_eat
    die 50 399 200 200 $times_to_eat
    die 50 400 200 200 $times_to_eat
    die 130 396 200 200 $times_to_eat
    die 130 399 200 200 $times_to_eat
    die 130 400 200 200 $times_to_eat
    die 198 396 200 200 $times_to_eat
    die 198 399 200 200 $times_to_eat
    die 198 400 200 200 $times_to_eat
}

uneven_die () {
    printf "${OBJ_COLOR}Testing uneven numbers - one should die${RESET}\n"
    die 4 310 200 100 $times_to_eat
    die 1 800 200 100 $times_to_eat
}

uneven_die_extended () {
    printf "${OBJ_COLOR}Testing uneven numbers - one should die${RESET}\n"
    die 3 596 200 200 $times_to_eat
    die 3 599 200 200 $times_to_eat
    die 3 600 200 200 $times_to_eat
    die 31 596 200 200 $times_to_eat
    die 31 599 200 200 $times_to_eat
    die 31 600 200 200 $times_to_eat
    die 131 596 200 200 $times_to_eat
    die 131 599 200 200 $times_to_eat
    die 131 600 200 200 $times_to_eat
    die 199 596 200 200 $times_to_eat
    die 199 599 200 200 $times_to_eat
    die 199 600 200 200 $times_to_eat
}

main () {
    mandatory_tests
    uneven_live
    uneven_live_extended
    even_live
    even_live_extended
    even_die
    even_die_extended
    uneven_die
    uneven_die_extended
}

main
