#ifndef SMARTUNIQ_METHODS_H
#define SMARTUNIQ_METHODS_H

extern void read_input(int input_fd, char ***lines, size_t *num_lines, int case_sensitive, int count);
extern void remove_duplicates(char ***lines, size_t *num_lines, int case_sensitive);
extern int compare_strings(const char *s1, const char *s2, int case_sensitive);
extern void print_with_count(char ***lines, size_t num_lines, int case_sensitive);

#endif
