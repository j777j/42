// Assignment name			: tsp
// Expected files			: *.c *.h
// Allowed functions   : write, sqrtf, getline, fseek, fscanf, ferror, feof, fabsf, memcpy, fprintf, fclose, malloc, calloc, realloc, free, fopen, errno, stderr, stdin, stdout
// -------------------------------------------------------

// The first publication referring to this problem as the "traveling salesman 
// problem" is found in the 1949 RAND Corporation report by Julia Robinson, 
// "On the Hamiltonian game (a traveling salesman problem)."

// Here is how she defines the problem:

// "The purpose of this note is to give a method for solving a problem related
// to the traveling salesman problem. It seems worthwhile to give a description
// of the original problem. One formulation is to find the shortest route for a
// salesman starting from Washington, visiting all the state capitals and then
// returning to Washington.

// More generally, to find the shortest CLOSED CURVE containing n given points 
// in the plane."

// for example with the following set of cities:
// 0, 0
// 1, 0
// 2, 0
// 0, 1
// 1, 1
// 2, 1
// 1, 2
// 2, 2
// which can be presented as follows:
// + + +
// + + +
//   + +
// the shortest path is:
//  _____
// |__   |
//    |__|

// so you should print the length of this path that is:
// 8.00

// Write a program that will read a set of city coordinates in the form 
// '%f, %f\n' from the standard input and will print the length of the shortest
// possible path containing all these cities under the form '%.2f'.

// Your program will not be tested with more than 11 cities.

// You will find in this directory a file tsp.c containing all the boring parts of
// this exercise and example files to help you test your program.

// hint: in order to use sqrtf, add -lm at the end of your compilation command.

// For example this should work:
// $> cat square.txt
// 1, 1
// 0, 1
// 1, 0
// 0, 0
// $> ./tsp < square.txt | cat -e
// 4.00$



#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

ssize_t size;//
float (*array)[2];//
float best_distance = 9999999.9;//
bool *visited;//
float dist;//
//
// compute the distance between two points
float    distance(float a[2], float b[2])
{
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

void   tsp(ssize_t current_city, float current_dist, float visited_count)//
{
    if (visited_count == size)//
    {//
        current_dist += distance(array[current_city], array[0]);//
        if (current_dist < best_distance)//
            best_distance = current_dist;//
        return ;//
    }//
    for (ssize_t i=0; i<size; i++)//
    {//
        if (visited[i]) continue;//
        dist = distance(array[current_city], array[i]);//
        if (dist + current_dist >= best_distance) continue;//
        visited[i] = true;//
        tsp(i, dist+current_dist, visited_count+1);//
        visited[i] = false;//
    }//
}

ssize_t    file_size(FILE *file)
{
    char    *buffer = NULL;
    size_t    n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int        retrieve_file(float (*array)[2], FILE *file)
{
    int tmp;
    for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++)
        if (tmp != 2)
        {
            errno = EINVAL;
            return -1;
        }
    if (ferror(file))
        return -1;
    return 0;
}

int        main(int ac, char **av)
{
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1)
    {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file)
    {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    size = file_size(file);//
    if (size == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    array = calloc(size, sizeof (float [2]));//
    if (!array)
    {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file) == -1)
    {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
        fclose(file);
    visited = calloc(size, sizeof(bool));//
    tsp(0, 0, 0);//
    printf("%.2f\n", best_distance);//
    free(array);
    return (0);
}