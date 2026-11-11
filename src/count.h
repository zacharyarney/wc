#ifndef WC_COUNT_H
#define WC_COUNT_H

#include <stddef.h>
#include <stdint.h>


struct Counts {
    size_t lineCt;
    size_t wordCt;
    size_t charCt;
    size_t byteCt;
    size_t longestLine;
};

/**
 * Processes files passed as command line parameters and prints the relevant
 * counts based on the selected flags.
 * @param argCt argc
 * @param args argv
 * @param idx index of first filename in argv returned by parseArgs
 * @param flags bit flags to determine output
 * @return 0 or 1 on success or fail
 */
int processFiles(int argCt, char *args[], int idx, uint8_t flags);

#endif // WC_COUNT_H
