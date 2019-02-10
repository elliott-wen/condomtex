#include <w2c/config.h>
#include "lib.h"
#include <kpathsea/variable.h>

/* Look up VAR_NAME in texmf.cnf; assign either the value found there or
   DFLT to *VAR.  */



void
setupboundvariable (integer *var, const_string var_name, integer dflt)
{
  
  *var = dflt;


  if(strcmp(var_name, "main_memory") == 0)
  {
    *var = 5000000;
  }
  else if (strcmp(var_name, "extra_mem_top") == 0)
  {
    *var = 0;
  }
  else if (strcmp(var_name, "extra_mem_bot") == 0)
  {
    *var = 0;
  }
  else if (strcmp(var_name, "pool_size") == 0)
  {
    *var = 6250000;
  }
  else if (strcmp(var_name, "string_vacancies") == 0)
  {
    *var = 90000;
  }
  else if (strcmp(var_name, "pool_free") == 0)
  {
    *var = 47500;
  }
  else if (strcmp(var_name, "max_strings") == 0)
  {
    *var = 500000;
  }
  else if (strcmp(var_name, "font_mem_size") == 0)
  {
    *var = 8000000;
  }
  else if (strcmp(var_name, "font_max") == 0)
  {
    *var = 9000;
  }
  else if (strcmp(var_name, "trie_size") == 0)
  {
    *var = 1000000;
  }
  else if (strcmp(var_name, "hyph_size") == 0)
  {
    *var = 8191;
  }
  else if (strcmp(var_name, "buf_size") == 0)
  {
    *var = 200000;
  }
  else if (strcmp(var_name, "nest_size") == 0)
  {
    *var = 500;
  }
  else if (strcmp(var_name, "max_in_open") == 0)
  {
    *var = 15;
  }
  else if (strcmp(var_name, "param_size") == 0)
  {
    *var = 10000;
  }
  else if (strcmp(var_name, "save_size") == 0)
  {
    *var = 100000;
  }
  else if (strcmp(var_name, "stack_size") == 0)
  {
    *var = 5000;
  }
  else if (strcmp(var_name, "dvi_buf_size") == 0)
  {
    *var = 16384;
  }
  else if (strcmp(var_name, "error_line") == 0)
  {
    *var = 79;
  }
  else if (strcmp(var_name, "half_error_line") == 0)
  {
    *var = 50;
  }
  else if (strcmp(var_name, "max_print_line") == 0)
  {
    *var = 79;
  }
  else if (strcmp(var_name, "hash_extra") == 0)
  {
    *var = 600000;
  }

}