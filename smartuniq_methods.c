#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <unistd.h>
#include <errno.h>
#include "smartuniq_methods.h"

void read_input(int input_fd, char ***lines, size_t *num_lines, int case_sensitive, int count)
{
    // creation of buffer and checking it
    size_t size_of_buffer = 4096;
    char *buffer = malloc(size_of_buffer);
    if (buffer == NULL) {
        perror("malloc");
        exit(0);
    }

    // reading input file
    int bytes_read;
    size_t return_total_bytes_read = 0;
    while ((bytes_read = read(input_fd, buffer +
    return_total_bytes_read, size_of_buffer - return_total_bytes_read)) > 0) {
        return_total_bytes_read += bytes_read;
        if (return_total_bytes_read == size_of_buffer) {
            // increase buffer size if it cannot hold the input file
            size_of_buffer++;
            buffer = realloc(buffer, size_of_buffer);
            if (buffer == NULL) {
                perror("realloc");
                exit(0);
            }
        }
    }
    if (bytes_read < 0) {
        perror("read");
        exit(EXIT_FAILURE);
    }
    // splitting buffer into lines
    size_t split_lines = 150;
    *lines = malloc(split_lines * sizeof(char *));
    if (*lines == NULL) {
        perror("malloc");
        exit(0);
    }
    // allocating memory into the line and copying it into an array
    size_t lines_read = 0;
    char *first_line = buffer;
    for (int i = 0; i < return_total_bytes_read; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            (*lines)[lines_read] = malloc(i - (first_line - buffer) + 1);
            if ((*lines)[lines_read] == NULL) {
                perror("malloc");
                exit(0);
            }
            strcpy((*lines)[lines_read], first_line);
            lines_read++;
            // increase size of array if it has filled up
            if (lines_read == split_lines) {
                split_lines++;
                *lines = realloc(*lines, split_lines * sizeof(char *));
                if (*lines == NULL) {
                    perror("realloc");
                    exit(0);
                }
            }
            first_line = buffer + i + 1;
        }
    }
    *num_lines = lines_read;
    // if user wants count, then print with count or simply remove the duplicates
    if (count) {
        print_with_count(lines, lines_read, case_sensitive);
    } else {
        remove_duplicates(lines, num_lines, case_sensitive);
        for (int i = 0; i < lines_read; i++) {
            if ((*lines)[i] != NULL) {
                printf("%s\n", (*lines)[i]);
            }
        }
    }
    free(buffer);

}

void remove_duplicates(char ***lines, size_t *num_lines, int case_sensitive)
{
     int new_lines = *num_lines;

    // going over each line in the array and checking if it was already removed
    for (int i = 0; i < new_lines; i++) {
        char *current_line = (*lines)[i];
        if (current_line == NULL) {
            continue;
        }

        // compare the current line with the other lines and checking if it was already removed
        for (int j = i + 1; j < new_lines; j++) {
            char *compare_line = (*lines)[j];
            if (compare_line == NULL) {
                continue;
            }

            // remove the line if it is a duplicate by using compare_strings method
            if (compare_strings(current_line, compare_line, case_sensitive) == 0) {
                (*lines)[j] = NULL;
                (*num_lines)--;
            }
        }
    }

    // shifting the lines and check if the lines were already removed
    int write = 0;
    for (int i = 0; i < new_lines; i++) {
        char *line = (*lines)[i];
        if (line == NULL) {
            continue;
        }
        (*lines)[write] = line;
        write++;
    }
    *num_lines = write;

    // make the rest of the lines null
    for (int i = write; i < new_lines; i++) {
        (*lines)[i] = NULL;
    }


}

int compare_strings(const char *s1, const char *s2, int case_sensitive)
{
    // compare the strings based on case_sensitive value
     if (case_sensitive == 0) {
        return strcmp(s1, s2);
    } else {
        return strcasecmp(s1, s2);
    }
}




void print_with_count(char ***lines, size_t num_lines, int case_sensitive)
{
    // if it is not case_sensitive, use strcasecmp to compare the
    // strings and make count increase and print count
    // else, simply use strcmp to compare and make count increase and print the count
    if (case_sensitive) {
        int count = 0;
        for (int i = 0; i < num_lines; i++) {
            count = 1;
            for (int j = i + 1; j < num_lines; j++) {
                if ((*lines)[i] != NULL && (*lines)[j] != NULL) {
                    if (strcasecmp((*lines)[i], (*lines)[j]) == 0) {
                        count++;
                    }
                }
            }
            if ((*lines)[i] != NULL) {
                printf("%i %s\n", count, (*lines)[i]);
                i += count - 1;
         }

        }
    } else {
        int count = 0;
        for (int i = 0; i < num_lines; i++) {
        count = 1;
        for (int j = i + 1; j < num_lines; j++) {
            if ((*lines)[i] != NULL && (*lines)[j] != NULL) {
                if (strcmp((*lines)[i], (*lines)[j]) == 0) {
                    count++;
                }
            }
        }
        if ((*lines)[i] != NULL) {
            printf("%i %s\n", count, (*lines)[i]);
            i += count - 1;
        }

        }
    }

}
