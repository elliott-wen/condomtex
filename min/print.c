#include "print.h"


unsigned char selector; /* where to print a message */ 
unsigned char dig[22]; /* digits in a number being output */ 
int tally; /* the number of characters recently printed */ 
unsigned int term_offset; /* the number of characters on the current  terminal line */ 
unsigned int file_offset; /* the number of characters on the current file line */ 

integer max_print_line; /* width of longest text lines output; should be at least 60 */ 
FILE *log_file; /* transcript of \TeX\ session */ 
FILE * write_file[16];

/* module 243 */
/*  Set variable |c| to the current escape character */
#define set_c_escape  c = escape_char

/* module 57 */
/* To end a line of text output, we call |print_ln|. */
void
print_ln (void) {  /* prints an end-of-line */
  switch (selector) {
  case term_and_log: 
	wterm_cr;
	wlog_cr;
	term_offset = 0;
	file_offset = 0;
	break;
  case log_only:
	wlog_cr;
	file_offset = 0;
	break;
  case term_only:
	wterm_cr;
	term_offset = 0;
	break;
  case no_print:
  case pseudo:
  case new_string:
	break;
  default:
	fprintf (write_file[selector],"\n");
  };
}; /* |tally| is not affected */