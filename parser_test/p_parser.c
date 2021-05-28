#include "p_parser.h"

FILE* FILE_TO_READ = NULL;

char BUFFER[SIZE_MAX_BUFFER];


const tag TAGS_LIST[] = {"nanoml", "document", "annexe", "section", "text", "li", "b", "h1", "li", "item"};
a_tag TAGS_LOADER = NULL;
tag TAG_TO_CLOSE = NULL;

a_content NANOML_LOADER = NULL;
a_content NANOML_TAG = NULL;

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

    while ((current_char = fgetc(file)) != EOF){

        // printf("%c", current_char);
        if (interprete_current_char(current_char)) {
            nb_tags++;
        }

        if (!is_empty_buffer()) {
            // print_buffer();
            // printf("Tag to close : %s\n", TAG_TO_CLOSE);
            empty_buffer();
            // print_tag_list(TAGS_LOADER);
        }

    }
    printf("\n%i tags crossed\n", nb_tags);

    // print_tag_list(TAGS_LOADER);
    print_all_content(NANOML_LOADER, 0);

    // Close the file
    fclose(file);

    return 1;
}

int interprete_current_char(char current_char) {
    // printf("Character evaluated : %c\n", current_char);
    if (!is_empty_buffer()) {
        empty_buffer();
    }

    // Read a tag
    if (current_char == '<') {

        char c;
        while((c = fgetc(FILE_TO_READ)) != '>') {
            add_char_to_buffer(c);
        }

        if (BUFFER[0] == '/') {
            if (read_closing_tag()) {
                char* current_tag = malloc(sizeof(BUFFER));

                int len_tag = sizeof(BUFFER);
    
                for (int i=1; i<len_tag; i++) {
                    current_tag[i-1] = BUFFER[i];
                }
                
                // printf("Closing tag : %s\n", current_tag);

                if (strcmp(current_tag, TAG_TO_CLOSE) == 0) {
                    if (remove_last_tag(TAGS_LOADER) != -1) {
                        TAG_TO_CLOSE = get_last_tag(TAGS_LOADER)->current_tag;
                        // printf("Tag to close is now : %s\n", TAG_TO_CLOSE);

                        if (NANOML_TAG->upper_content != NULL) {
                            NANOML_TAG = NANOML_TAG->upper_content;
                        }
                    }
                } else {
                    printf("Error, tag '%s' foundt when '%s' was expected\n", current_tag, TAG_TO_CLOSE);
                }
                
            }

        } 
        else {
            if (read_opening_tag()) {
                
                // Create a char* label for the tag

                char* current_tag = malloc(sizeof(BUFFER));

                int len_tag = sizeof(BUFFER);
                
                for (int i=0; i<len_tag; i++) {
                    current_tag[i] = BUFFER[i];
                }

                // printf("Opening tag : %s\n", current_tag);

                a_content nanoml_content = init_content(current_tag);

                // If the TAGS_LOADER is null we need to instantiate it
                if (TAGS_LOADER == NULL) {
                    // printf("At tag %s, loader was null\n", current_tag);
                    TAGS_LOADER = create_tag(current_tag);
                    NANOML_LOADER = nanoml_content;

                } else {
                    add_brother(TAGS_LOADER, current_tag);
                    add_sub_content(NANOML_TAG, nanoml_content);
                }

                TAG_TO_CLOSE = get_last_tag(TAGS_LOADER)->current_tag;
                NANOML_TAG = nanoml_content;
            }

            // fseek(FILE_TO_READ, -1, SEEK_CUR);
        }

        return 1;

    } else if (current_char == ' ' || current_char == '\n') {
        printf("Skipping blank space\n");
        return 0;
    }
    
    else {
        // printf("\nTag to close %s\n", NANOML_TAG->tag);
        // printf("\nEvalutating %c\n", current_char);

        a_text text_content = create_empty_text(0);

        add_char_to_buffer(current_char);

        char c;
        while ((c = fgetc(FILE_TO_READ)) != '<') {
            // printf("For char %c\n", c);
            if (c == ' ' || c == '\n' || c == '<') {
                char* current_word = malloc(sizeof(BUFFER));
                strcpy(current_word, BUFFER);

                if (strcmp(current_word, " ") == 1) {
                    a_word word = create_word(current_word, 0);
                    add_word_to_text(text_content, word);
                    add_space_to_text(text_content);
                }

                empty_buffer();

            } else {
                add_char_to_buffer(c);
            }
        }

        if (!is_empty_buffer() && !(strcmp(BUFFER, " ") == 0)) {
            char* current_word = malloc(sizeof(BUFFER));
            strcpy(current_word, BUFFER);
            a_word word = create_word(current_word, 0);
            add_word_to_text(text_content, word);
            add_space_to_text(text_content);

            empty_buffer();
        }

        // printf("\nText registered:\n");
        // print_text(text_content);

        a_content subcontent = init_content("txt");
        subcontent->text_content = text_content;

        add_sub_content(NANOML_TAG, subcontent);

        fseek(FILE_TO_READ, -1, SEEK_CUR);
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
        // printf("The buffer is empty\n");
        return 0;
    }
    
    printf("%s\n", BUFFER);
    return 1;
}

int empty_buffer() {
    if (is_empty_buffer()) {
        // printf("The buffer is empty\n");
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



/* ======================= TAGS_LOADER ======================= */

a_tag create_tag(tag current_tag) {
    // printf("Creating tag : %s\n", current_tag);
    a_tag new_tag = (a_tag) malloc(sizeof(t_tag));

    new_tag->current_tag = current_tag;
    new_tag->next_brother = NULL;
    
    return new_tag;
}

int is_null_tag(a_tag tag) {
    return tag == NULL;
}

int print_tag(a_tag tag) {
    if (is_null_tag(tag)) {
        printf("Cannot perform action with empty tags\n");
        return 0;
    }

    printf("%s (%p)\n", tag->current_tag, tag);
    if (!is_null_tag(tag->next_brother)) {
        printf("\t%s\n", tag->next_brother->current_tag);
    } else {
        printf("\tNULL\n");
    }

    return 1;
}

int add_brother(a_tag current_tag, tag brother) {
    if (is_null_tag(current_tag)) {
        printf("Cannot perform action with empty tags\n");
        return 0;
    }

    // Make tag point to brother

    a_tag new_b = create_tag(brother);

    get_last_tag(current_tag)->next_brother = new_b;

    
    return 0;
}

a_tag get_last_tag(a_tag tag) {
    if (is_null_tag(tag)) {
        printf("Cannot perform action with empty tags\n");
        return 0;
    }

    if (is_null_tag(tag->next_brother)) {
        // printf("Le dernier tag est %s\n", tag->current_tag);
        return tag;
    }

    return get_last_tag(tag->next_brother);
}

int remove_last_tag(a_tag tag) {
    if (is_null_tag(tag)) {
        printf("Cannot perform action with empty tags\n");
        return 0;
    }

    a_tag last_element = get_last_tag(tag);

    a_tag current_tag = tag;

    if (current_tag == last_element) {
        // printf("Removing last element\n");
        return -1;
        
    } else {
        while (current_tag->next_brother != last_element) {
            current_tag = current_tag->next_brother;
        }

        current_tag->next_brother = NULL;
        free(last_element);

        return 1;
    }
    
}

int print_tag_list(a_tag current_tag) {
    if (is_null_tag(current_tag)) {
        printf("Cannot perform action with empty tags\n");
        return 0;
    }

    print_tag(current_tag);

    if (current_tag->next_brother != NULL) {
        print_tag_list(current_tag->next_brother);
    }

    return 1;
}