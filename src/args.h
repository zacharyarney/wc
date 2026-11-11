#ifndef WC_ARGS_H
#define WC_ARGS_H

#include <stdint.h>


/**
 * Iterates through command line arguments, differentiating and validating
 * filenames and flags.
 * @param argsCount
 * @param args
 * @param bitFlags
 * @return index of first filename in argv or -1 on failure
 */
int parseArgs(int argsCount, char *args[], uint8_t *bitFlags);

#endif // WC_ARGS_H
