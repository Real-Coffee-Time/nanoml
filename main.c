#include <stdlib.h>
#include <stdio.h>

#include "parser_test/p_parser.h"
#include "nanoml_loader/p_nanoml_loader.h"
#include "cli_render/p_cli_render.h"

int main(int argc, char** argv) {
    printf("Hello World !\n");
    
    char* file_path = "assets/test.nanoml";

    init_parser(file_path);

    parse_file();

    return 0;
}