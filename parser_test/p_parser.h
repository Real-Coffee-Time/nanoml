#ifndef P_PARSER_H
#define P_PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "../nanoml_loader/p_nanoml_loader.h"
#include "../cli_render/p_cli_render.h"

#define SIZE_MAX_BUFFER 500

typedef char* tag;

/* ======================= TAGS_LOADER ======================= */

typedef struct s_tag {
    tag current_tag;
    struct s_tag* next_brother;
} t_tag;

typedef t_tag* a_tag;

/***/
a_tag create_tag(tag current_tag);

/***/
int is_null_tag(a_tag tag);

/***/
int add_brother(a_tag current_tag, tag brother);

/***/
int remove_last_tag(a_tag tag);

/***/
int print_tag_list(a_tag tag);

/***/
int print_tag(a_tag tag);

/***/
a_tag get_last_tag(a_tag tag);

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