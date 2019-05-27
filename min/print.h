#ifndef CONSTANT_HEADER
#define CONSTANT_HEADER
#include <texmfmp.h>
#include <stdio.h>

#define term_in  stdin
#define term_out  stdout


#define no_print 16
#define term_only 17
#define log_only 18
#define term_and_log 19
#define pseudo 20
#define new_string 21
#define max_selector 21
/* module 56 */

/* Macro abbreviations for output to the terminal and to the log file are
 * defined here for convenience. Some systems need special conventions
 * for terminal output, and it is possible to adhere to those conventions
 * by changing |wterm|, |wterm_ln|, and |wterm_cr| in this section.
 */
#define wterm( arg )  zwrite ( term_out , arg )
#define wlog( arg )  zwrite ( log_file , arg )

#define wterm_string(arg)  fprintf ( term_out , "%s", arg )
#define wlog_string(arg)  fprintf ( log_file , "%s", arg )

#define wterm_char(arg)  fprintf ( term_out , "%c", arg )
#define wlog_char(arg)  fprintf ( log_file , "%c", arg )

#define wterm_cr  fprintf ( term_out , "\n")
#define wlog_cr  fprintf ( log_file , "\n")

/* module 60 */
#define slow_print  zprint
/* module 68 */

/* Old versions of \TeX\ needed a procedure called |print_ASCII| whose function
 * is now subsumed by |zprint|. We retain the old name here as a possible aid to
 * future software arch\ae ologists.
 */
#define print_ASCII  zprint


#endif