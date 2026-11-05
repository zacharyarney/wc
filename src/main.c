#include "args.h"

#include <stdint.h>
#include <stdio.h>


int main(int argc, char *argv[]) {

    printf("\n");
    printf("argc: %d", argc);
    printf("\n");

    uint8_t flags = 0;

    return parseArgs(argc, argv, &flags);
}
