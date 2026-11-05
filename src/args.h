#ifndef WC_ARGS_H
#define WC_ARGS_H

#include "constants.h"

#include <stdbool.h>
#include <stdint.h>


// default args are -clw
enum {
    FLAG_LINES = 1u << 0, // 00000001
    FLAG_WORDS = 1u << 1, // 00000010
    FLAG_CHARS = 1u << 2, // 00000100
    FLAG_BYTES = 1u << 3, // 00001000
    FLAG_LINE_LEN = 1u << 4, // 00010000
};

typedef char Filename[WC_MAX_PATH_LEN];

/**
 * Checks if any flags have been set.
 * @param bitFlags
 * @return bool
 */
bool isDefault(uint8_t bitFlags);

/**
 * Iterates through flags after single-dash arg.
 * @param cmdLineFlags, bitFlags
 * @return int
 */
int setShortFlags(const char *cmdLineFlags, uint8_t *bitFlags);

/**
 * Iterates through command line arguments, differentiating and validating
 * filenames and flags.
 * @param argsCount, args, bitFlags
 * @return int
 */
int parseArgs(int argsCount, char *args[], uint8_t *bitFlags);

#endif // WC_ARGS_H
