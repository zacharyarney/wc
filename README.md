# wc

Re-implementation of `wc` command-line utility written in c99.

## GNU wc manpage

```text
NAME
       wc - word, line, and byte or character count

SYNOPSIS
       wc [OPTION]... [FILE]...
       wc [OPTION]... --files0-from=F

DESCRIPTION
       Print newline, word, and byte counts for each FILE, and a total line if more than one FILE is specified.  A
       word is a nonempty sequence of non white space delimited by white space characters or by start or end of input.

       With no FILE, or when FILE is -, read standard input.

       The options below may be used to select which counts are printed, always in the following order: newline, word,
       character, byte, maximum line length.

       -c, --bytes
              print the byte counts

       -m, --chars
              print the character counts

       -l, --lines
              print the newline counts

       --debug
              indicate what line count acceleration is used

       --files0-from=F
              read input from the files specified by NUL-terminated names in file F; If F is -, read names from
              standard input

       -L, --max-line-length
              print the maximum display width

       -w, --words
              print the word counts

       --total=WHEN
              when to print a line with total counts; WHEN can be: auto, always, only, never

       --help display this help and exit

       --version
              output version information and exit

AUTHOR
       Written by Paul Rubin and David MacKenzie.

REPORTING BUGS
       Report bugs to: <bug-coreutils@gnu.org>.
       Report any translation bugs to: <https://translationproject.org/team/>.
       GNU coreutils home page: <https://www.gnu.org/software/coreutils/>
       General help using GNU software: <https://www.gnu.org/gethelp/>

COPYRIGHT
       Copyright © 2026 Free Software Foundation, Inc.  License GPLv3+: GNU GPL version 3 or later
       <https://gnu.org/licenses/gpl.html>.
       This is free software: you are free to change and redistribute it.  There is NO WARRANTY, to the extent
       permitted by law.

SEE ALSO
       Full documentation <https://www.gnu.org/software/coreutils/wc>
       or available locally via: info '(coreutils) wc invocation'

GNU coreutils 9.12                                  September 2026                                               WC(1)
```

## BSD wc manpage

```text
WC(1)                       General Commands Manual                      WC(1)

NAME
     wc – word, line, character, and byte count

SYNOPSIS
     wc [--libxo] [-Lclmw] [file ...]

DESCRIPTION
     The wc utility displays the number of lines, words, and bytes contained
     in each input file, or standard input (if no file is specified) to the
     standard output.  A line is defined as a string of characters delimited
     by a ⟨newline⟩ character.  Characters beyond the final ⟨newline⟩
     character will not be included in the line count.

     A word is defined as a string of characters delimited by white space
     characters.  White space characters are the set of characters for which
     the iswspace(3) function returns true.  If more than one input file is
     specified, a line of cumulative counts for all the files is displayed on
     a separate line after the output for the last file.

     The following options are available:

     --libxo
             Generate output via libxo(3) in a selection of different human
             and machine readable formats.  See xo_parse_args(3) for details
             on command line arguments.

     -L      Write the length of the line containing the most bytes (default)
             or characters (when -m is provided) to standard output.  When
             more than one file argument is specified, the longest input line
             of all files is reported as the value of the final “total”.

     -c      The number of bytes in each input file is written to the standard
             output.  This will cancel out any prior usage of the -m option.

     -l      The number of lines in each input file is written to the standard
             output.

     -m      The number of characters in each input file is written to the
             standard output.  If the current locale does not support
             multibyte characters, this is equivalent to the -c option.  This
             will cancel out any prior usage of the -c option.

     -w      The number of words in each input file is written to the standard
             output.

     When an option is specified, wc only reports the information requested by
     that option.  The order of output always takes the form of line, word,
     byte, and file name.  The default action is equivalent to specifying the
     -c, -l and -w options.

     If no files are specified, the standard input is used and no file name is
     displayed.  The prompt will accept input until receiving EOF, or [^D] in
     most environments.

     If wc receives a SIGINFO (see the status argument for stty(1)) signal,
     the interim data will be written to the standard error output in the same
     format as the standard completion message.

ENVIRONMENT
     The LANG, LC_ALL and LC_CTYPE environment variables affect the execution
     of wc as described in environ(7).

EXIT STATUS
     The wc utility exits 0 on success, and >0 if an error occurs.

EXAMPLES
     Count the number of characters, words and lines in each of the files
     report1 and report2 as well as the totals for both:

           wc -mlw report1 report2

     Find the longest line in a list of files:

           wc -L file1 file2 file3 | fgrep total

COMPATIBILITY
     Historically, the wc utility was documented to define a word as a
     “maximal string of characters delimited by <space>, <tab> or <newline>
     characters”.  The implementation, however, did not handle non-printing
     characters correctly so that “  ^D^E  ” counted as 6 spaces, while
     “foo^D^Ebar” counted as 8 characters.  4BSD systems after 4.3BSD modified
     the implementation to be consistent with the documentation.  This
     implementation defines a “word” in terms of the iswspace(3) function, as
     required by IEEE Std 1003.2 (“POSIX.2”).

     The -L option is a non-standard FreeBSD extension, compatible with the -L
     option of the GNU wc utility.

SEE ALSO
     iswspace(3), libxo(3), xo_parse_args(3)

STANDARDS
     The wc utility conforms to IEEE Std 1003.1-2001 (“POSIX.1”).

HISTORY
     A wc command appeared in Version 1 AT&T UNIX.

macOS 26.5                      April 11, 2020                      macOS 26.5
```

## Arg parsing

- if argc < 2
    - stdin mode (TODO)
- if argv[i] == '--'
    - treat as "end of args" delimiter
    - set end args flag to treat all following args as filenames (this is how to process files that start with `-`)
- check the first character
    - if arg[0] !== '-'
        - treat as filename, run the wc process against file
        - all following args should also be counted as filename
        - store counts in struct, append struct to output array
        - struct might also contain filename (as FAM?)
            - otherwise, filename already exists in argv, but index will not line up with output array index.
        - if file not found, set struct values to -1
    - in case where arg[0] == '-' and no filename or `--` has already been encountered
        - iterate through entire arg checking that each character is valid flag
        - if invalid flag character is encountered, throw invalid arg error, exit
        - set local bool for each valid flag (maybe a toggle for char vs byte flags)
        - if all characters are valid flags, set local flag bools to corresponding bools in state struct

## Output logic

- pass argv and output array to output function.
    - trade-off here between iterating through args on each iteration and storing O (1)-access flags for each included
      flag
        - Can be done on the stack as these variables only need to be scoped to the output function, booleans are just
          one bit.
        - Flags probably make more sense
- iterate through output array and use fprintf to build each line of output.
- on each iteration, add each count to local accumulator variables for total.
- if value encountered < 0, print error message with filename