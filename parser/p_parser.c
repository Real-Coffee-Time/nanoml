#include "p_parser.h"

char mon_caractere;

int parse_file(char* file_name) {
    FILE* file_to_parse = fopen(file_name, "r");

    if (file_to_parse == NULL) {
        printf("An error occured while opening the file : %s", file_name);
        return 0;
    }

    char line[LINE_MAX_SIZE];

    // Read line by line (to change to char by char)
    while (fgets(line, LINE_MAX_SIZE, file_to_parse) != NULL){

        printf("%s", line);
    
    }

    printf("\n");

    // 
    fseek(file_to_parse, 0, SEEK_SET);
    mon_caractere = fgetc(file_to_parse);
    printf("%c\n", mon_caractere);

    // Close the file
    fclose(file_to_parse);

    return 1;
}

void lire_contenu() {

    if (lire_mot() == "<section>") {
        while (lire_mot() == "</section>") {

            lire_section();

        }
    }

}

void lire_annexes() {

    // lit le contenu entre les balises d'annexes
    if (lire_mot() == "<annexe>") {
        while (lire_mot != "</annexe>") {

            lire_contenu();

        }
    } else {
        exit(0);
    }

    // dans le cas où il y a plusieurs annexes
    lire_annexes();

}

void lire_texte_enrichi() {

    lire_document();
    lire_annexes();

}