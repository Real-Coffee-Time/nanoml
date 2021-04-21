#include <stdlib.h>
#include <stdio.h>

#include "parser/p_parser.h"

int main(int argc, char** argv) {
    printf("Hello World !\n");

    parse_file("assets/test.nanoml");
    
    return 0;
}