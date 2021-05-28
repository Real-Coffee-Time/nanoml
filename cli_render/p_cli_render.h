#ifndef P_CLI_RENDER_H
#define P_CLI_RENDER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../parser_test/p_parser.h"
#include "../nanoml_loader/p_nanoml_loader.h"

#define MAX_WIDTH 75

/**
 * Remet le buffer à 0. 
 * Prends en compte le nombre de section.
*/
void initialize_buffer ();

/**
 * Affiche le buffer
*/
void print_BUFFER ();

/**
 * Met les valeurs textuelles dans le buffer
*/
void print_texte( a_text text, int is_title);

/**
 * Mets le contenu des titres en majuscules dans le buffer
*/
void print_title(char* text);

/**
 * @params: a_content content la structure n-aire
 * applique l'affichage sur l'ensemble de la structure
*/
void print_nanoml (a_content content);

/**
 * affiche les lignes de délimitaition de section
*/
void print_closing_line();


#endif