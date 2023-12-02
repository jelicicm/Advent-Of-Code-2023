#include "stdlib.h"
#include "stdio.h"
#include <assert.h>
#include <ctype.h>
#include <string.h>

const unsigned total_red = 12;
const unsigned total_green = 13;
const unsigned total_blue = 14;

#define PART_2 0

char* get_number_from_string(char* pos, unsigned* ret_val) {
    char num[10];
    int i = 0;
    while(isdigit(*pos)) { num[i] = *pos; pos++; i++;}
    num[i] = '\0';
    *ret_val = atoi(num);
    return pos;
}

char* get_game_id(char* line, unsigned* game_id) {
    return get_number_from_string(line, game_id);
}

char* get_color_from_string(char *pos, char* color) {
    int i = 0;
    while (*(pos+i) != '\n' && *(pos+i) != ';' && *(pos+i) != ',') {
        i++;
    }

    memcpy(color, pos, i);

    color[i] = '\0';
    return pos+i-1;
}

int parse_line_for_validity(const char* line) {
    char* it = line+5; // avoid "Game " at the start of line
    unsigned game_id;
    it = get_game_id(it, &game_id);
    
    it = strstr(line, ":") + 1;

    unsigned num = 0;

    unsigned red_max = 0;
    unsigned green_max = 0;
    unsigned blue_max = 0;
    while(*it != '\n') {
        char color[10];

        if (isdigit(*it)) {
            it = get_number_from_string(it, &num);
            // printf("Extracted number: %3u, now string: %s", num, it);
        }
        else if (isalpha(*it)) {
            it = get_color_from_string(it, color);
            // printf("Extracted color: %s, now string: %s\n", color, it);
            assert(num > 0);
            if (strcmp(color, "green") == 0) {
                green_max = (num > green_max) ? num : green_max;
            } else if (strcmp(color, "red") == 0) {
                red_max = (num > red_max) ? num : red_max;
            } else {
                blue_max = (num > blue_max) ? num : blue_max;
            }
            num = 0;
        }
        else if (*it == ' ') { }
        else if (*it == ';') { }
        it++;
    }

#if !PART_2
    if ((red_max <= total_red) && (blue_max <= total_blue) && (green_max <= total_green)) {
        return game_id;
    } else {
        return -1;
    }
#else
    return red_max * blue_max * green_max;
#endif
}

int main(int argc, char* argv[]) {

    FILE* fp = fopen(argv[1], "r");
    size_t read_bytes = 0;
    char* line = NULL;
    size_t len;

    unsigned int total_sum = 0;

    while ((read_bytes = getline(&line, &len, fp)) != -1) {
        // printf("%s", line);

        int valid_id = parse_line_for_validity(line);
        total_sum = (valid_id > 0) ? (total_sum + valid_id) : total_sum;
    }

    fclose(fp);

    printf("Total sum = %d\n", total_sum);

    return 0;
}