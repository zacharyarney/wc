#include "args.h"
#include "count.h"

#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    uint8_t flags = 0;
    const int argIndex = parseArgs(argc, argv, &flags);
    if (argIndex < 0) return 1;

    printf("argc: %d\n", argc);
    return processFiles(argc, argv, argIndex, flags);
}
