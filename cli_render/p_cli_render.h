#ifndef P_CLI_RENDER_H
#define P_CLI_RENDER_H

#include <stdlib.h>
#include <stdio.h>

// #include "../parser/p_parser.h"

#define MAX_WIDTH 75

/***/
void print_line(char* text);

/***/
void print_title(char* text);

/***/
void print_section(char* text, int width);

/***/
void print_closing_line(int max_width);

#endif