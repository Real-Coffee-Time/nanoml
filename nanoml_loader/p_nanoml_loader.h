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

/**
 * Créer un mot
 * @param string word : le mot
 * @param int is_important : le degré d'importance
 * @return a_word : le noeud créé
*/
a_word create_word(string word, int is_important);

/**
 * Créer un texte sans mot
 * @param int is_title : indique si le texte est un titre
 * @return a_text : le texte
*/
a_text create_empty_text(int is_title);

/**
 * Créer un expace
 * @return a_word : un espace
*/
a_word create_space();

/**
 * Ajoute un espace dans un texte
 * @param a_text text : le texte auquel il faut ajouter un espace
 * @return int : 0 si le texte est NULL, 1 sinon
*/
int add_space_to_text(a_text text);

/**
 * Ajoute un mot à un texte
 * @param a_text text : le texte auquel il faut ajouter un mot
 * @param a_word word : le mot à ajouter au texte
 * @return int : 0 si le texte ou le mot est NULL, 1 sinon
*/
int add_word_to_text(a_text text, a_word word);

/**
 * Indique si un mot est NULL
 * @param  a_word word : le mot à tester
 * @return int : 1 si oui, 0 sinon
*/
int is_null_word(a_word word);

/**
 * Affiche un mot
 * @param a_word word : le mot à afficher
 * @return int : 0 si le mot est NULL, 1 sinon
*/
int print_word(a_word word);

/**
 * Affiche un mot en majuscules
 * @param a_word word : le mot à afficher
 * @return int : 0 si le mot est NULL, 1 sinon
*/
int print_word_in_maj(a_word word);

/**
 * Affiche un texte
 * @param a_text text : le texte à afficher
 * @return int : 0si le texte est null, 1 sinon
*/
int print_text(a_text text);

/**
 * Renvoi un texte
 * @param a_texte text : le texte à renvoyer
 * @return char* : le texte
*/
char* return_text(a_text text);

/**
 * Indique si un texte est NULL
 * @param a_texte text : le texte à tester
 * @return int : 1 si oui, 0 sinon
*/
int is_null_text(a_text text);

/* ========================= CONTENT ========================= */

/**
 * Initialise un contenu
 * @param char* tag : le tag
 * @return a_content : le content
*/
a_content init_content(char* tag);

/**
 * Indique si un content est NULL
 * @return int : 1 si oui, 0 sinon
*/
int is_null_content(a_content content);

/**
 * Affiche un content
 * @return int : 0 si le content est NULL, 1 sinon
*/
int print_content(a_content content);

/**
 * Ajoute un content suivant au content
 * @param a_content content : le content qui gagne un suivant
 * @param a_content next_content : le content qui devient le suivant
 * @return int : 0 si l'un des content est NULL, 1 sinon
*/
int add_next_content(a_content content, a_content next_content);

/**
 * Ajoute un sous content au content
 * @param a_content content : le content qui recoi un sous content
 * @param a_content sub_content : le sous content du content
 * @return int : 0 si l'un des content est NULL, 1 sinon
*/
int add_sub_content(a_content content, a_content sub_content);

/**
 * Affiche l'ensemble des content
 * @param a_content content : le content initial
 * @param int indent : l'indentation d'affichage
 * @return int : 0 si le content est null, 1 sinon
*/
int print_all_content(a_content content, int indent);

#endif