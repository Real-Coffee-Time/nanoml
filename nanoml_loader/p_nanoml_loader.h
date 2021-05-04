#ifndef P_NANOML_LOADER_H
#define P_NANOML_LOADER_H

#include <stdlib.h>
#include <stdio.h>

#define CONTENT_TYPE a_text | a_list

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
} t_text;

typedef t_text* a_text;

typedef struct s_list {
    a_text text;
    struct s_list** items;
    int nb_of_items;
} t_list;

typedef t_list* a_list;

typedef struct s_content {
    a_text* text;
    a_list* lists;
    struct s_content** sub_content;
} t_content;

typedef t_content* a_content;

typedef struct s_section {
    a_content* contents;
    int nb_content;
} t_section;

typedef t_section* a_section;

typedef struct s_nanoml {
    a_section document;
    a_section annexe;
} t_nanoml;

typedef t_nanoml* a_nanoml;

/* ========================= WORDS ========================= */

/* ========================= LISTS ========================= */

/* ======================== CONTENT ======================== */


#endif