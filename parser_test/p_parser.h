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

/**
 * Cree un nouveau tag
 * @param tag current_tag : le current_tag du nouveau tag
 * @return a_tag : le nouveau tag
*/
a_tag create_tag(tag current_tag);

/**
 * Vérifie si un tag est NULL
 * @param a_tag tag : le tag à vérifier
 * @return int : 1 si le tag est null, 0 sinon
*/
int is_null_tag(a_tag tag);

/**
 * Ajoute un tag frere à un tag existant
 * @param a_tag current_tag : le tag qui reçoit un frère
 * @param tag brother : le tag frère
 * @return int : 1 si ca fonctionne, 0 sinon
*/
int add_brother(a_tag current_tag, tag brother);

/**
 * Supprime le dernier tag frere 
 * @param a_tag tag : tag dont il faut supprimer le dernier frère
 * @return int : 0 si le tag est NULL, 1 si le dernier tag est supprimé, -1 sinon
*/
int remove_last_tag(a_tag tag);

/**
 * Affiche l'ensemble des tags frères
 * @param a_tag tag : le tag dont il faut afficher tous les frères suivants
 * @return int : 1 si les tags s'affichent, 0 si tag est NULL
*/
int print_tag_list(a_tag tag);

/**
 * Affiche un tag
 * @param a_tag tag : le tag à afficher
 * @return int : 1 si il s'affiche, 0 si il est NULL
*/
int print_tag(a_tag tag);

/**
 * Va chercher le dernier tag frère
 * @param a_tag tag : le tag dont on veut récupérer le dernier frère
 * @return a_tag : le dernier frère
*/
a_tag get_last_tag(a_tag tag);

/* ========================= PARSER ========================= */

/**
 * Ouvre le fichier à parser et l'enregistre dans une variable globale
 * @return int : 0 si le fichier est NULL, 1 sinon
*/
int init_parser();

/**
 * Parcours le fichier afin de créer la structure n-aire,
 * Affiche la structure n-aire, puis le fichier formaté
 * @return 0 si le fichier est NULL, 1 si tout se passe bien
*/
int parse_file();

/**
 * défini le comportement du parseur en fonction du caractère parcouru
 * @param char current_char : le caractere à parcourir
 * @return int : 1 dès qu'elle croise '<' ou '>', 0 sinon
*/
int interprete_current_char(char current_char);

/* ========================== TAGS ========================== */

/**
 * lit une balise ouvrante
 * @return int : 1 si la balise existe, 0 sinon
*/
int read_opening_tag();

/**
 * lit une balise fermante
 * @return int : 1 si la balise existe, 0 sinon
*/
int read_closing_tag();

/**
 * Dit si un tag existe ou non
 * @param tag tested_tag : le tag à tester
 * @return int : 1 si il existe, 0 sinon
*/
int is_existing_tag(tag tested_tag);

/* ========================= BUFFER ========================= */

/**
 * ajoute un caractère au buffer en cours
 * @param char charactere : le caractere à ajouter
 * @return int : 0 si le buffer est plein, 1 sinon
*/
int add_char_to_buffer(char character);

/**
 * affiche le buffer en cours
 * @return int : 0 si le buffer est vide, 1 sinon
*/
int print_buffer();

/**
 * Vide le buffer
 * @return int : 0 si il est déjà vide, 0 sinon
*/
int empty_buffer();

/**
 * Indique si le buffer est vide
 * @return int : 1 si oui, 0 sinon
*/
int is_empty_buffer();

#endif