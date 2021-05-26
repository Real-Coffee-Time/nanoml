#ifndef P_PARSER_H
#define P_PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE_MAX_BUFFER 500

typedef char* tag;

/* ========================= PARSER ========================= */

/***/
int init_parser();

/***/
int parse_file();

/***/
int interprete_current_char(char current_char);

/* ========================== TAGS ========================== */

/***/
int read_opening_tag();

/***/
int read_closing_tag();

/***/
int is_existing_tag(tag tested_tag);

/* ========================= BUFFER ========================= */

/***/
int add_char_to_buffer(char character);

/***/
int print_buffer();

/***/
int empty_buffer();

/***/
int is_empty_buffer();

#endif