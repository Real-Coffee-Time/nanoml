#include <stdlib.h>
#include <stdio.h>

#include "parser/p_parser.h"

int main(int argc, char** argv) {
    printf("Hello World !\n");

    char* file_name = "assets/test.nanoml";

    parse_file(file_name);
    
    return 0;
}