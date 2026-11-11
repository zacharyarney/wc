#include "count.h"

#include "constants.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <wctype.h>


static size_t countLinesWords(char buf[],
                              struct Counts *cts,
                              size_t *lineLen,
                              const size_t numBytes) {
    size_t i = 0;
    bool inWord = true;
    bool inSpace = false;
    for (; i < numBytes; i++) {
        // count words
        inSpace = isspace(buf[i]);
        if (inSpace && inWord) cts->wordCt += 1;
        inWord = !inSpace;
        // count line length
        if (buf[i] == '\t') {
            *lineLen += (8 - (*lineLen % 8));
        } else if (isprint(buf[i])) {
            *lineLen += 1;
        }
        // count lines
        if (buf[i] == '\n') {
            cts->lineCt += 1;
            if (*lineLen > cts->longestLine) cts->longestLine = *lineLen;
            *lineLen = 0;
        }
    }
    if (!inSpace && i < WC_MAX_READ) {
        cts->wordCt += 1;
        if (*lineLen > cts->longestLine) cts->longestLine = *lineLen;
    }

    return 0;
}


static int readFile(FILE *curFile, struct Counts *curCts, char *curArg) {
    char fileBuf[WC_MAX_READ];
    size_t bytesRead;
    size_t curLineLen = 0;

    while ((bytesRead = fread(fileBuf, sizeof(char), WC_MAX_READ, curFile))) {
        if (ferror(curFile)) {
            printf("Error opening file %s", curArg);
            if (fclose(curFile) == EOF) {
                printf("Error closing file %s", curArg);
            }
            return -1;
        }

        countLinesWords(fileBuf, curCts, &curLineLen, bytesRead);
        curCts->charCt += bytesRead;
        curCts->byteCt += bytesRead;

        if (feof(curFile)) break;
    }

    if (fclose(curFile) == EOF) {
        printf("Error closing file %s", curArg);
    }

    return 0;
}


static int
doCounts(const int argCt, char *args[], int idx, struct Counts filesCts[]) {
    const int firstFileIdx = idx;

    for (; idx < argCt; idx++) {
        char *curArg = args[idx];
        struct Counts curCts = filesCts[idx - firstFileIdx];
        if (strcmp(curArg, "-") == 0) {
            printf("TODO: implement stdin (dash)\n");
            continue;
        }
        FILE *curFile = fopen(curArg, "r");
        if (curFile == NULL) {
            printf("wcz: %s: No such file or directory\n", curArg);
            return -1;
        }

        // TODO: what if file is a directory?

        if (readFile(curFile, &curCts, curArg) != 0) {
            return -1;
        }

        printf("%ld %ld %ld %ld %ld %s\n",
               curCts.lineCt,
               curCts.wordCt,
               curCts.charCt,
               curCts.byteCt,
               curCts.longestLine,
               args[idx]);
    }

    return 0;
}


int processFiles(const int argCt,
                 char *args[],
                 const int idx,
                 const uint8_t flags) {
    if (idx >= argCt) {
        printf("TODO: implement stdin (no args)\n");
    }

    struct Counts filesCts[argCt - idx];
    memset(filesCts, 0, sizeof(filesCts));

    if (doCounts(argCt, args, idx, filesCts) != 0) {
        return -1;
    }

    printf("flags: %d\n", flags);
    return 0;
}
