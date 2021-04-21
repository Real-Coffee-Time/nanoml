#include "p_parser.h"

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

    // Close the file
    fclose(file_to_parse);

    return 1;
}