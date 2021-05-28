#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "p_cli_render.h"

void print_closing_line(int max_width) {
    printf("|");
    for (int i=0; i<max_width; i++) {
        printf("-");
    }
    printf("|\n");
}

void print_section(char* text, int width) {
    print_closing_line(width);
    

    int index = 0;
    while (text[index] != '\0') {
        printf("|");
        for (int i=0; i<width;  i++) {
            if (text[index] != '\0') {
                printf("%c", text[index]);
                index++;
            } else {
                printf(" ");
            }
        }
        printf("|\n");
    }
}