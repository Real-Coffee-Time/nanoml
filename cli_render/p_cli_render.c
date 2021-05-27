#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "p_cli_render.h"

void print_line(char* text) {

    printf ("%s \n", text);

}

void print_title(char* text) {

    for (int i=0 ; text[i] != '\0' ; i++) {
        
        printf("%c", text[i]-32);

    }

    printf(" \n");

}