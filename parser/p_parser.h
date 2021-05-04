#ifndef P_PARSER_H
#define P_PARSER_H

#include <stdlib.h>
#include <stdio.h>

/**
 * --------------------- PARSER ---------------------
 * 
 * @author Anatole de Chauveron, Adrien Ducourthial
 * 
 * Function to parse a file
*/

#define LINE_MAX_SIZE 250

/**
 * -------------------- GRAMMAR --------------------
 * 
 * Grammar to use for the project
*/

/**
 * Function that loads a folder content and parse the content.
 * @param FILE* file_name: The name of the file to parse
 * @returns Int : 1 if parse was executed without problem, 0 if an error occured while parsing the file
*/
int parse_file(char* file_name);

/**
 * @param caractere : la lettre à lire
 * Ecrit la lettre dans un fichier
*/
void lire_charactere(char caractere);

/**
 * Lit toutes les lettres d'un mot
*/
void lire_mot_simple();

/**
 * Lit un mot simple
 * Applique les *
*/ 
void lire_mot_important();

/**
 * Lit un mot simple
 * Ou un mot important 
 * Ou un retour à la ligne
*/
void lire_mot_enrichi();

/**
 * Lit un nombre de mot enrichis compris entre 0 et plusieurs
*/
void lire_texte();

/**
 * Lit un texte puis une liste
*/ 
void lire_texte_liste();

/**
 * Lit une liste puis texte_liste
*/
void lire_liste_texte();

/**
 * Lit un texte liste ou un liste texte compris entre les balises <item> et </item>
*/
void lire_item();

/**
 * Lit l'ensemble des items compris entre les balises <liste> et </liste>
*/
void lire_liste();

/**
 * Lit un texte compris entre les balises <titre> et </titre>
 * Applique les majuscules
*/
void lire_titre();

/**
 * Lit l'ensemble des sections, titres, mots_enrichis et listes qui existent
*/
void lire_contenu();

/**
 * Lit le contenu entre les balises <section> et </section>
*/
void lire_section();

/**
 * Lit le contenu entre les balises <document> et </document>
*/
void lire_document();

/**
 * Lit le contenu entre <annexe> et </annexe> pour chaques balises <annexe> ouvertes
*/
void lire_annexes();

/**
 * Lit document puis lit annexe
*/
void lire_texte_enrichi();

#endif