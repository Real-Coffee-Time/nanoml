#ifndef P_NANOML_LOADER_H
#define P_NANOML_LOADER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef char* string;

typedef struct s_word {
    string word;
    int is_important;
} t_word;

typedef t_word* a_word;

typedef struct s_text {
    a_word* text;
    int nb_words;
    int is_title;
    int nb_char;
} t_text;

typedef t_text* a_text;

typedef struct s_content {
    char* tag;
    a_text text_content;
    struct s_content* next_content;
    struct s_content* sub_content;
    struct s_content* previous_content;
    struct s_content* upper_content;
} t_content;

typedef t_content* a_content;

/* ========================= WORDS ========================= */

/***/
a_word create_word(string word, int is_important);

/***/
a_text create_empty_text();

/***/
a_word create_space();

/***/
int add_space_to_text(a_text text);

/***/
int add_space_to_text(a_text text);

/***/
int add_word_to_text(a_text text, a_word word);

/***/
int add_space_to_text(a_text text);

/***/
int is_null_word(a_word word);

/***/
int print_word(a_word word);

/***/
int print_word_in_maj(a_word word);

/***/
int print_text(a_text text);

/***/
char* return_text(a_text text);

/***/
int is_null_text(a_text text);

/* ========================= CONTENT ========================= */

/***/
a_content init_content(char* tag);

/***/
int is_null_content(a_content content);

/***/
int print_content(a_content content);

/***/
int add_next_content(a_content content, a_content next_content);

/***/
int add_sub_content(a_content content, a_content sub_content);

/***/
a_content get_upper_content(a_content inside_content, a_content content);

/***/
int print_all_content(a_content content, int indent);

#endif