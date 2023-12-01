#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "assert.h"
#include "ctype.h"

#define PART_2 0

#if PART_2
const char* letter_numbers[] = {"one", "two", "three", "four",
                   "five", "six", "seven", "eight", "nine"};
#endif

const char* int_numbers[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static char *last_strstr(const char *haystack, const char *needle)
{
    // shamelessly stolen from: https://stackoverflow.com/a/1643946
    if (*needle == '\0')
        return (char *) haystack;

    char *result = NULL;
    for (;;) {
        char *p = strstr(haystack, needle);
        if (p == NULL)
            break;
        result = p;
        haystack = p + 1;
    }

    return result;
}


unsigned get_number_from_line(char* line) {
    int i = 0;
    int left_index = strlen(line);
    int right_index = -1;

    int left_number = -1;
    int right_number = -1;

#if PART_2
    for (i = 0; i < 9; i++) {
        char* left_pos = strstr(line, letter_numbers[i]);
        char* right_pos = last_strstr(line, letter_numbers[i]);

        if (left_pos != NULL) {
            if ((left_pos - line) < left_index) {
                left_index = (left_pos - line);
                left_number = i + 1; 
            }
        }
        if (right_pos != NULL) {
            if ((right_pos - line) > right_index) {
                right_index = (right_pos - line);
                right_number = i + 1; 
            }
        }
    }
#endif

    for (i = 0; i < 9; i++) {
        char* left_pos = strstr(line, int_numbers[i]);
        char* right_pos = last_strstr(line, int_numbers[i]);

        if (left_pos != NULL) {
            if ((left_pos - line) < left_index) {
                left_index = (left_pos - line);
                left_number = i + 1; 
            }
        }
        if (right_pos != NULL) {
            if ((right_pos - line) > right_index) {
                right_index = (right_pos - line);
                right_number = i + 1; 
            }
        }
    }

    assert(left_number >= 0);
    assert(right_number >= 0);

    return left_number*10 + right_number;
}


int main(int argc, char* argv[]) {

    unsigned int total_sum = 0;
    char* filepath = argv[1];
    FILE *fp = fopen(filepath, "r");

    if (fp == NULL) {
        exit(-1);
    }

    size_t read_bytes = 0;
    char *line = NULL;
    size_t len = 0;

    while ((read_bytes = getline(&line, &len, fp)) != -1) {
        unsigned two_digit_number = get_number_from_line(line);
        // printf("%s: %d\n", line, two_digit_number);
        total_sum += two_digit_number;
    }

    printf("Total sum = %d\n", total_sum );
    return total_sum;
}