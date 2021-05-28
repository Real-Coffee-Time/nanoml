#include "p_nanoml_loader.h"

/* ========================= WORDS ========================= */

a_word create_word(string word, int is_important) {
    a_word new_word = (a_word) malloc(sizeof(t_word));

    new_word->word = word;
    new_word->is_important = is_important;

    return new_word;
}

int is_null_word(a_word word) {
    return word == NULL;
}

a_word create_space() {
    return create_word(" ", 0);
}

int print_word(a_word word) {
    if (is_null_word(word)) {
        printf("Cannot print null word.\n");
        return 0;
    }
    
    if (word->is_important) {
        printf("*%s*", word->word);
    } else {
        printf("%s", word->word);
    }
    return 1;
}

int print_word_in_maj(a_word word) {
    if (is_null_word(word)) {
        printf("Cannot print null word.\n");
        return 0;
    }

    char temp[250] = {0};

    for (int i = 0; word->word[i] != '\0'; i++){
        unsigned char c = word->word[i];
        if (isalnum(c)) {
            temp[i] = toupper(c);
        } else {
            temp[i] = c;
        }
    }

    printf("%s", temp);

    return 1;
}

a_text create_empty_text(int is_title) {
    a_text new_text = (a_text) malloc(sizeof(t_text));

    new_text->nb_words = 0;
    new_text->is_title = is_title;
    new_text->nb_char = 0;

    return new_text;
}

int is_null_text(a_text text) {
    return text == NULL;
}

int add_word_to_text(a_text text, a_word word) {
    if (is_null_text(text) | is_null_word(word)) {
        printf("Cannot add word to text with empty values.\n");
        return -1;
    }

    if (text->nb_words == 0) {
        text->text = (a_word*) malloc(sizeof(a_word));
        text->text[0] = word;
        text->nb_words++;
    } else {
        text->text = (a_word*) realloc(text->text, sizeof(a_word) * (text->nb_words + 1));
        text->text[text->nb_words] = word;
        text->nb_words++;
    }

    text->nb_char += strlen(word->word);

    return 1;
}

int add_space_to_text(a_text text) {
    if (is_null_text(text)) {
        printf("Cannot add space to null text.\n");
        return 0;
    }

    return add_word_to_text(text, create_space());
}

char* return_text(a_text text) {
    if (is_null_text(text)) {
        printf("Cannot return null text.\n");
        return 0;
    }

    char* str_text = malloc(sizeof(char) * text->nb_char);

    int index=0;
    for (int i=0; i<text->nb_words; i++) {
        for (int j=0; j<strlen(text->text[i]->word); j++) {
            str_text[index] = text->text[i]->word[j];
            index++;
        }
    }

    return str_text;
}

int print_text(a_text text) {
    if (is_null_text(text)) {
        printf("Cannot print null text.\n");
        return 0;
    }

    for (int i=0; i<text->nb_words; i++) {
        print_word(text->text[i]);
    }

    return 1;
}


/* ========================= CONTENT ========================= */

a_content init_content(char* tag) {
    a_content new_content = (a_content) malloc(sizeof(t_content));

    new_content->tag = tag;
    new_content->text_content = create_empty_text(0);
    new_content->sub_content = NULL;
    new_content->next_content = NULL;
    new_content->previous_content = NULL;
    new_content->next_content = NULL;

    return new_content;
}

int is_null_content(a_content content) {
    return content == NULL;
}

int print_content(a_content content) {
    if (is_null_content(content)) {
        printf("Cannot print null content\n");
        return 0;
    }

    printf("\n%s (%p)\n\t", content->tag, content);
    print_text(content->text_content);

    return 1;
}

int add_next_content(a_content content, a_content next_content) {
    if (is_null_content(content) || is_null_content(next_content)) {
        printf("Cannot perform action with null content\n");
        return 0;
    }

    content->next_content = next_content;
    next_content->previous_content = content;
    next_content->upper_content = content->upper_content;

    return 1;
}

int add_sub_content(a_content content, a_content sub_content) {
    if (is_null_content(content) || is_null_content(sub_content)) {
        printf("Cannot perform action with null content\n");
        return 0;
    }

    // Go to the last sub_content and add a brother


    if (content->sub_content == NULL) {
        content->sub_content = sub_content;
    } else {
        a_content sub = content->sub_content;

        while (sub->next_content != NULL) {
            sub = sub->next_content;
        }

        sub->next_content = sub_content;
        sub_content->previous_content = sub;
        printf("Adding %s after %s\n", sub_content->tag, sub->tag);
    }

    sub_content->upper_content = content;

    return 1;
}

int print_all_content(a_content content, int indent) {
    if (is_null_content(content)) {
        printf("Cannot print null content\n");
        return 0;
    }
    // printf("indent %i\n", indent);
    for (int i=0; i<indent; i++) {
        printf("\t");
    }
    

    printf("%s (%p)\n", content->tag, content);

    // if (content->next_content != NULL) {
    //     for (int i=0; i<indent +1; i++) {
    //         printf("\t");
    //     }
    //     printf("[next_content : %s (%p)]\n", content->next_content->tag, content->next_content);
    // }

    // if (content->sub_content != NULL) {
    //     for (int i=0; i<indent +1; i++) {
    //         printf("\t");
    //     }
    //     printf("[sub_content : %s (%p)]\n", content->sub_content->tag, content->sub_content);
    // }

    for (int i=0; i<indent + 1; i++) {
        printf("\t");
    }
    print_text(content->text_content);
    printf("\n");


    if (content->sub_content != NULL) {
        // printf("Moving to print sub_content %s\n", content->sub_content->tag);
        int sub_indent = indent;
        sub_indent += 1;
        print_all_content(content->sub_content, sub_indent);
    }

    if (content->next_content != NULL) {
        print_all_content(content->next_content, indent);
    }

    // printf("\n");

    return 1;
}