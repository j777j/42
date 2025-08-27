#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <float.h>

// compute the distance between two points
float distance(float a[2], float b[2]) {
    return sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1] - a[1]));
}

void tsp_recursive(ssize_t size, float (*array)[2], bool *visited, float *best_distance, ssize_t current_city, float current_dist, int visited_count) {
    if (visited_count == size) {
        current_dist += distance(array[current_city], array[0]);
        if (current_dist < *best_distance) {
            *best_distance = current_dist;
        }
        return;
    }

    for (ssize_t i = 0; i < size; i++) {
        if (!visited[i]) {
            float dist = distance(array[current_city], array[i]);
            if (current_dist + dist >= *best_distance) {
                continue;
            }
            visited[i] = true;
            tsp_recursive(size, array, visited, best_distance, i, current_dist + dist, visited_count + 1);
            visited[i] = false;
        }
    }
}

float solve_tsp(float (*array)[2], ssize_t size) {
    if (size <= 1) {
        return 0.0;
    }

    bool *visited = calloc(size, sizeof(bool));
    if (!visited) {
        return -1.0;
    }

    float best_distance = FLT_MAX;
    visited[0] = true;
    tsp_recursive(size, array, visited, &best_distance, 0, 0.0, 1);

    free(visited);
    return best_distance;
}

ssize_t file_size(FILE *file) {
    char *buffer = NULL;
    size_t n = 0;
    ssize_t ret;

    errno = 0;

    for (ret = 0; getline(&buffer, &n, file) != -1; ret++);

    free(buffer);
    if (errno || fseek(file, 0, SEEK_SET))
        return -1;
    return ret;
}

int retrieve_file(float (*array)[2], FILE *file, ssize_t size) {
    int tmp;
    for (size_t i = 0; i < size && (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i] + 1)) != EOF; i++) {
        if (tmp != 2) {
            errno = EINVAL;
            return -1;
        }
    }
    if (ferror(file))
        return -1;
    return 0;
}

int main(int ac, char **av) {
    char *filename = "stdin";
    FILE *file = stdin;
    if (ac > 1) {
        filename = av[1];
        file = fopen(filename, "r");
    }

    if (!file) {
        fprintf(stderr, "Error opening %s: %m\n", filename);
        return 1;
    }

    ssize_t size = file_size(file);
    if (size == -1) {
        fprintf(stderr, "Error reading %s: %m\n", filename);
        fclose(file);
        return 1;
    }

    float (*array)[2] = calloc(size, sizeof(float[2]));
    if (!array) {
        fprintf(stderr, "Error: %m\n");
        fclose(file);
        return 1;
    }

    if (retrieve_file(array, file, size) == -1) {
        fprintf(stderr, "Error reading %s: %m\n", av[1]);
        fclose(file);
        free(array);
        return 1;
    }
    if (ac > 1)
        fclose(file);

    float result = solve_tsp(array, size);
    if (result < 0) {
        fprintf(stderr, "Error: TSP solver failed\n");
        free(array);
        return 1;
    }

    printf("%.2f\n", result);
    free(array);
    return (0);
}
