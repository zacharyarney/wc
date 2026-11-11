#ifndef WC_CONSTANTS_H
#define WC_CONSTANTS_H


#define WC_MAX_PATH_LEN  4096
#define WC_MAX_FILES_BUF 1048576 // 1MB
#define WC_MAX_READ 16384   // 16KiB

#define FLAG_LINES    (1u << 0u) // 00000001
#define FLAG_WORDS    (1u << 1u) // 00000010
#define FLAG_CHARS    (1u << 2u) // 00000100
#define FLAG_BYTES    (1u << 3u) // 00001000
#define FLAG_LINE_LEN (1u << 4u) // 00010000

#endif // WC_CONSTANTS_H
