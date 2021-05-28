#ifndef P_CLI_RENDER_H
#define P_CLI_RENDER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../parser_test/p_parser.h"
#include "../nanoml_loader/p_nanoml_loader.h"

#define MAX_WIDTH 75

/**
 * Reinitialise le buffer
 * Prends en compte le nombre de section.
*/
void initialize_buffer ();

/**
 * Ecrits sur le terminal une ligne complete du document
*/
void print_BUFFER ();

/**
 * Inscrits les valeurs textuelles dans le buffer
*/
void print_texte( a_text text, int is_title);

/**
 * Inscrits le contenu des titres en majuscules dans le buffer
*/
void print_title(char* text);

/**
 * Affiche l'ensemble du fichier nanoml en respectant le format
 * @param a_content content : la structure n-aire
*/
void print_nanoml (a_content content);

/**
 * affiche les lignes de délimitaition de section
*/
void print_closing_line();


#endif