#include <stdlib.h>
#include <stdio.h>

#include "parser_test/p_parser.h"
#include "nanoml_loader/p_nanoml_loader.h"

int main(int argc, char** argv) {
    printf("Hello World !\n");
    
    char* file_path = "assets/test.nanoml";

    init_parser(file_path);

    // parse_file();

    // a_tag t = init_tag_loader("nanoml");
    // add_brother(t, "document");

    // print_tag_list(t);

    // remove_last_tag(t);
    // printf("%s\n",get_last_tag(t)->current_tag);

    a_text text = create_empty_text();
    text->is_title = 1;

    a_word mot = create_word("Un", 0);
    a_word mot1 = create_word("texte", 0);
    a_word mot2 = create_word("important", 1);
    a_word mot3 = create_word(".", 0);

    add_word_to_text(text, mot);
    add_space_to_text(text);
    add_word_to_text(text, mot1);
    add_space_to_text(text);
    add_word_to_text(text, mot2);
    add_word_to_text(text, mot3);

    a_content content = init_content(text);
    print_content(content);


    return 0;
}