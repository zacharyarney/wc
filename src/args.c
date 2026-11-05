#include "args.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


static bool endOfArgs = false;

static const char *illegalOptText = "wc: invalid option -- ";
static const char *usageText = "usage: [-lwmcL] [file ...]";


bool isDefault(const uint8_t bitFlags) {
    return bitFlags == 0;
}


int setShortFlags(const char *cmdLineFlags, uint8_t *bitFlags) {
    const size_t argLen = strlen(cmdLineFlags);

    for (size_t ii = 1; ii < argLen; ii++) {
        switch (cmdLineFlags[ii]) {
        case 'l':
            *bitFlags |= FLAG_LINES;
            printf("l for lines\n");
            continue;
        case 'w':
            *bitFlags |= FLAG_WORDS;
            printf("w for words\n");
            continue;
        case 'm':
            *bitFlags |= FLAG_CHARS;
            printf("m for characters\n");
            continue;
        case 'c':
            *bitFlags |= FLAG_BYTES;
            printf("c for bytes\n");
            continue;
        case 'L':
            *bitFlags |= FLAG_LINE_LEN;
            printf("L for line length\n");
            continue;
        default:
            printf("%s%c\n", illegalOptText, cmdLineFlags[ii]);
            printf("%s\n", usageText);
            return 1;
        }
    }
    return 0;
}


int parseArgs(const int argsCount, char *args[], uint8_t *bitFlags) {
    for (int i = 1; i < argsCount; i++) {
        char *curArg = args[i];
        if (strcmp(curArg, "--") == 0 && !endOfArgs) {
            endOfArgs = true;
            printf("This is the end of the arguments. All files from here on out\n");
            continue;
        }
        if (curArg[0] == '-' && !endOfArgs) {
            printf("argv[%d]: %s (length=%lu)\n", i, curArg, strlen(curArg));
            if (setShortFlags(curArg, bitFlags) != 0) return 1;
            continue;
        }
        endOfArgs = true;
        printf("This is a file. Try to open it. See what happens\n");
    }
    return 0;
}
