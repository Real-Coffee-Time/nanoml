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

#endif