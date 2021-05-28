#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "p_cli_render.h"

char BUFFER[MAX_WIDTH];         // une ligne de l'affichage
int char_in_buffer = 0;         // le nombre de caractères présent sur la ligne en cours
int NB_SECTION = 0;             
int is_title = 0;

void initialize_buffer () {

    for (int i=0 ; i<MAX_WIDTH ; i++) {
        if (i < NB_SECTION || i > MAX_WIDTH-NB_SECTION-1) {
            BUFFER[i] = '|';
        }
        else {
            BUFFER[i] = ' ';
        }
    }

    char_in_buffer = 0;

}

void print_BUFFER () {

    for (int i=0 ; i<MAX_WIDTH ; i++) {
        printf("%c", BUFFER[i]);
    }
    printf("\n");

}

void print_closing_line() {

    BUFFER[NB_SECTION] = '+';
    for (int i=1 ; i<MAX_WIDTH-(2*NB_SECTION)-1 ; i++) {
        BUFFER[NB_SECTION + i] = '-';
    }
    BUFFER[MAX_WIDTH - (NB_SECTION+1)] = '+';

    print_BUFFER();
    initialize_buffer();
}

void print_texte(a_text text, int is_title) {

    char* new = NULL;
    new = (char*) malloc( sizeof(char) * MAX_WIDTH+1 );
    strcpy(new, "");

    for (int i=0 ; i<text->nb_words ; i++) {

        strcat(new, text->text[i]->word);

    }

    int j = 0;

    if (is_title == 1) {
        print_title(new);
    } 
    else {
        for(int i = 0 ; i < strlen(new) ; i++) {
            if (BUFFER[char_in_buffer + (2*NB_SECTION) + i - j] >= MAX_WIDTH) {
                j = i;
                print_BUFFER();
                initialize_buffer();
            }
            BUFFER[char_in_buffer + (NB_SECTION+i) - j] = new[i];
        }
    } 

    char_in_buffer += strlen(new);

}

void print_title(char* text) {

    int j = 0;

    for (int i = 0 ; i < strlen(text) ; i++) {
        if (BUFFER[char_in_buffer + (2*NB_SECTION) + i - j] >= MAX_WIDTH) {
                j = i;
                print_BUFFER();
                initialize_buffer();
            }
        if (text[i] >= 'a' && text[i] <= 'z') {
            BUFFER[char_in_buffer + (NB_SECTION+i)] = text[i]-32;
        }
        else {
            BUFFER[char_in_buffer + (NB_SECTION+i)] = text[i];
        }
    }

}

void print_nanoml(a_content content) {

    if (is_null_content(content)) {

        //printf("Cannot print null content\n");

    }
    else if ( strcmp( content->tag, "nanoml" ) == 0 ) {

        print_nanoml(content->sub_content);

    }
    else if ( strcmp( content->tag, "document" ) == 0 ) {
        
        print_closing_line();
        NB_SECTION++;
        print_nanoml(content->sub_content);
        NB_SECTION--;
        print_closing_line();
        print_nanoml(content->next_content);

    }
    else if ( strcmp( content->tag, "annexes" ) == 0 ) {

        print_closing_line();
        NB_SECTION++;
        initialize_buffer();
        print_nanoml(content->sub_content);
        NB_SECTION--;
        print_BUFFER();
        print_closing_line();
        print_nanoml(content->next_content);
        
    }
    else if ( strcmp( content->tag, "contenu" ) == 0 ) {

        print_nanoml(content->sub_content);
        print_nanoml(content->next_content);
        
    }
    else if ( strcmp( content->tag, "section" ) == 0 ) {

        print_BUFFER();
        print_closing_line();
        NB_SECTION++;
        print_nanoml(content->sub_content);
        NB_SECTION--;
        print_BUFFER();
        print_closing_line();
        print_nanoml(content->next_content);
        
    }
    else if ( strcmp( content->tag, "titre" ) == 0 ) {

        initialize_buffer();
        is_title = 1;
        print_texte(content->text_content, is_title);
        print_nanoml(content->sub_content);
        print_BUFFER();
        initialize_buffer();
        is_title = 0;
        print_nanoml(content->next_content);
        
    }
    else if ( strcmp( content->tag, "txt" ) == 0 ) {

        print_texte(content->text_content, is_title);
        print_nanoml(content->next_content);
        
    }
    else if ( strcmp( content->tag, "mot_important" ) == 0 ) {
        
        BUFFER[char_in_buffer+1] = '*';
        char_in_buffer++;
        print_texte(content->text_content, is_title);
        print_nanoml(content->sub_content);
        BUFFER[char_in_buffer] = '*';
        char_in_buffer++;
        print_nanoml(content->next_content);

    }
    else if ( strcmp( content->tag, "liste") == 0 ) {

        initialize_buffer();
        print_nanoml(content->sub_content);
        print_nanoml(content->next_content);
        
    }
    else if ( strcmp(content->tag, "item") == 0 ) {

        print_BUFFER();
        initialize_buffer();
        for (int i=0 ; i<5 ; i++) {
            if (i==2) {
                BUFFER[NB_SECTION+char_in_buffer+i] = '#';
            }
            else {
                 BUFFER[NB_SECTION+char_in_buffer+i] = ' ';
            }
        }
        char_in_buffer += 5;
        print_nanoml(content->sub_content);
        print_nanoml(content->next_content);
        
    }

}