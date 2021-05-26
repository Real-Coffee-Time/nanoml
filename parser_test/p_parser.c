#include "p_parser.h"

const tag TAGS_LIST[] = {"document", "annexe", "section", "text", "li", "b", "h1", "li", "item"};
char BUFFER[SIZE_MAX_BUFFER];
FILE* FILE_TO_READ = NULL;

/* ========================= PARSER ========================= */

int init_parser(char* file_name) {

    FILE* file_to_parse = fopen(file_name, "r");

    if (file_to_parse == NULL) {
        printf("An error occured while opening the file : %s", file_name);
        return 0;
    }

    FILE_TO_READ = file_to_parse;

    return 1;
}

int parse_file() {

    FILE* file = FILE_TO_READ;

    if (file == NULL) {
        printf("Cannot parse null file.\n");
        return 0;
    }

    char current_char;
    int nb_tags = 0;

    // Read line by line (to change to char by char)
    while ((current_char = fgetc(file)) != EOF){

        // printf("%c", current_char);
        if (interprete_current_char(current_char)) {
            nb_tags++;
        }

        if (!is_empty_buffer()) {
            print_buffer();
            empty_buffer();
        }

    }
    printf("%i tags crossed", nb_tags);

    // Close the file
    fclose(file);

    return 1;
}

int interprete_current_char(char current_char) {
    // printf("Character evaluated : %c\n", current_char);make r
    if (!is_empty_buffer()) {
        empty_buffer();
    }

    // Read a tag
    if (current_char == '<') {
        

        // char c = fgetc(FILE_TO_READ);

        // do {
        //     add_char_to_buffer(c);
        // } while((c = fgetc(FILE_TO_READ)) != '>');

        char c;
        while((c = fgetc(FILE_TO_READ)) != '>') {
            add_char_to_buffer(c);
        }

        if (BUFFER[0] == '/') {
            read_closing_tag();
        } else {
            read_opening_tag();
        }
        // print_buffer();
        fseek(FILE_TO_READ, -1, SEEK_CUR);

        return 1;

    } else if (isalnum(current_char)) {

        add_char_to_buffer(current_char);
        char c;

        while(isalnum(c = fgetc(FILE_TO_READ))) {
            add_char_to_buffer(c);
        }
        fseek(FILE_TO_READ, -1, SEEK_CUR);
        return 0;

    } else if (current_char == '.' || current_char == ',' || current_char == ':' || current_char == '!' || current_char == '?') {

        add_char_to_buffer(current_char);

        return 0;

    } else {

        return 0;
    }

    return 0;
}



/* ========================== TAGS ========================== */

int is_existing_tag(tag tested_tag) {

    int nb_tags = sizeof(TAGS_LIST) / sizeof(TAGS_LIST[0]);
    int index = 0;

    for (int i=0; i<nb_tags; i++) {
        if (strcmp(tested_tag, TAGS_LIST[index]) == 0) {
            return 1;
        }
        index++;
    }

    return 0;
}

int read_opening_tag() {

    if (is_existing_tag(BUFFER)) {
        return 1;
    }

    return 0;
}

int read_closing_tag() {    

    int len_tag = sizeof(BUFFER);
    char temp_tag[len_tag - 1];
    
    for (int i=1; i<len_tag; i++) {
        temp_tag[i-1] = BUFFER[i];
    }

    if (is_existing_tag(temp_tag)) {
        return 1;
    }

    return 0;
}



/* ========================= BUFFER ========================= */

int add_char_to_buffer(char character) {
    int index = 0;
    while (BUFFER[index] != '\0') {
        index++;
    }

    if (index == SIZE_MAX_BUFFER) {
        printf("The buffer is full\n");
        return 0;
    }

    BUFFER[index] = character;
    return 1;
}

int print_buffer() {
    if (is_empty_buffer()) {
        printf("The buffer is empty\n");
        return 0;
    }
    
    printf("%s\n", BUFFER);
    return 1;
}

int empty_buffer() {
    if (is_empty_buffer()) {
        printf("The buffer is empty\n");
        return 0;
    }

    for (int i=0; i<SIZE_MAX_BUFFER; i++) {
        BUFFER[i] = '\0';
    }
    return 1;
}

int is_empty_buffer() {
    for (int i=0; i<SIZE_MAX_BUFFER; i++) {
        if (BUFFER[i] != '\0') {
            return 0;
        }
    }
    return 1;
}