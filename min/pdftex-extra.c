#define	EXTERN /* Instantiate data from pdftexd.h here.  */

#include <pdftexd.h>
string fullnameoffile;
string output_directory;
int ac;
char **av;
int tfmtemp;
int texinputtype;
int kpse_make_tex_discard_errors;
string translate_filename;
const_string c_job_name;
char start_time_str[32];
char *last_source_name;
int last_lineno;
const char *ptexbanner = " (pdfTeX Standalone Experiment)";
const char *DEFAULT_FMT_NAME = " pdflatex.fmt";
const char *DEFAULT_DUMP_NAME = "pdflatex";
string versionstring = " (pdfTeX Standalone 0.1 beta)";

#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <md5.h>



void *xmalloc(size_t newsize)
{
	void *ptr = malloc(newsize);
	if(!ptr)
	{
		fprintf(stderr, "Malloc Failed");
		abort();
	}
	memset(ptr, 0, newsize);
	return ptr;
}

void* xrealloc(void* oriptr, size_t newsize)
{
	void *ptr = realloc(oriptr, newsize);
	if(!ptr)
	{
		fprintf(stderr, "Realloc Failed");
		abort();
	}
	return ptr;
}

FILE *
xfopen (const_string filename,  const_string mode)
{
    FILE *f;

    //assert(filename && mode);

    f = fopen(filename, mode);
    if (f == NULL)
    {

        fprintf(stderr, "File Open Failed (%s)\n", filename);
        abort();
    }

    return f;
}





int xfclose ( FILE * stream,  const_string filename )
{
	int ret = fclose(stream);	
	if(ret != 0)
	{
		fprintf(stderr, "File Close Failed %s", filename);
		abort();
	}
	return 0;
}

void
close_file (FILE *f)
{
  if (!f)
    return;
  xfclose(f, "closefile");
}

boolean
kpse_absolute_p (const_string filename, boolean relative_ok)
{
  boolean absolute;
  boolean explicit_relative;

  absolute = IS_DIR_SEP (*filename);
  explicit_relative   = relative_ok;
  return absolute || explicit_relative;
}

boolean
dir_p (string fn)
{
  struct stat stats;
  return stat (fn, &stats) == 0 && S_ISDIR (stats.st_mode);
}

void
recorder_record_input (const_string name)
{
    
}

/* record an output file name */
void
recorder_record_output (const_string name)
{
    
}


string
concat3 (const_string s1,  const_string s2,  const_string s3)
{
  int s2l = s2 ? strlen (s2) : 0;
  int s3l = s3 ? strlen (s3) : 0;
  string answer
      = (string) xmalloc (strlen(s1) + s2l + s3l + 1);
  strcpy (answer, s1);
  if (s2) strcat (answer, s2);
  if (s3) strcat (answer, s3);

  return answer;
}


boolean
open_input (FILE **f_ptr, int filefmt, const_string fopen_mode)
{
    string fname = NULL;


    *f_ptr = NULL;
    if (fullnameoffile)
        free(fullnameoffile);
    fullnameoffile = NULL;
    
    /* Look in -output-directory first, if the filename is not
       absolute.  This is because .aux and other such files will get
       written to the output directory, and we have to be able to read
       them from there.  We only look for the name as-is.  */

    if (output_directory && !kpse_absolute_p (nameoffile+1, false)) {

        fname = concat3 (output_directory, "/", nameoffile + 1);
        *f_ptr = fopen (fname, fopen_mode);

/*
    if fname is a directory, discard it.
*/
        if (*f_ptr && dir_p (fname)) {
            fclose (*f_ptr);
            *f_ptr = NULL;
        }

        if (*f_ptr) {

            free (nameoffile);
            namelength = strlen (fname);
            nameoffile = xmalloc (namelength + 2);
            strcpy (nameoffile + 1, fname);
            fullnameoffile = fname;
        } else {
            free (fname);
        }
    }

    /* No file means do the normal search. */
    if (*f_ptr == NULL) {
        /* A negative FILEFMT means don't use a path.  */
        if (filefmt < 0) {
            /* no_file_path, for BibTeX .aux files and MetaPost things.  */
            *f_ptr = fopen(nameoffile + 1, fopen_mode);
            /* FIXME... fullnameoffile = xstrdup(nameoffile + 1); */
        } else {
            
            boolean must_exist;
            must_exist = (filefmt != kpse_tex_format || texinputtype)
                    && (filefmt != kpse_vf_format);
            fname = kpse_find_file (nameoffile + 1,
                                    (kpse_file_format_type)filefmt,
                                    must_exist);
            if (fname) {
                fullnameoffile = xstrdup(fname);
                /* If we found the file in the current directory, don't leave
                   the `./' at the beginning of `nameoffile', since it looks
                   dumb when `tex foo' says `(./foo.tex ... )'.  On the other
                   hand, if the user said `tex ./foo', and that's what we
                   opened, then keep it -- the user specified it, so we
                   shouldn't remove it.  */
                if (fname[0] == '.' && IS_DIR_SEP (fname[1])
                    && (nameoffile[1] != '.' || !IS_DIR_SEP (nameoffile[2])))
                {
                    unsigned i = 0;
                    while (fname[i + 2] != 0) {
                        fname[i] = fname[i + 2];
                        i++;
                    }
                    fname[i] = 0;
                }
                *f_ptr = xfopen (fname, fopen_mode);

                /* kpse_find_file always returns a new string. */
                free (nameoffile);
                namelength = strlen (fname);
                nameoffile = xmalloc (namelength + 2);
                strcpy (nameoffile + 1, fname);
                free (fname);
            }
        }
    }

    if (*f_ptr) {
        recorder_record_input (nameoffile + 1);

       
        if (filefmt == kpse_tfm_format) {
            tfmtemp = getc (*f_ptr);
        } else if (filefmt == kpse_ofm_format) {
            tfmtemp = getc (*f_ptr);
        }
    }            

    return *f_ptr != NULL;
}

boolean
open_output (FILE **f_ptr, const_string fopen_mode)
{
    string fname;
    boolean absolute = kpse_absolute_p(nameoffile+1, false);

    /* If we have an explicit output directory, use it. */
    if (output_directory && !absolute) {
        fname = concat3(output_directory, "/", nameoffile + 1);
    } else {
        fname = nameoffile + 1;
    }

    /* Is the filename openable as given?  */
    *f_ptr = fopen (fname, fopen_mode);

    
    /* If this succeeded, change nameoffile accordingly.  */
    if (*f_ptr) {
        if (fname != nameoffile + 1) {
            free (nameoffile);
            namelength = strlen (fname);
            nameoffile = xmalloc (namelength + 2);
            strcpy (nameoffile + 1, fname);
        }
        recorder_record_output (fname);
    }
    if (fname != nameoffile +1)
        free(fname);
    return *f_ptr != NULL;
}

boolean
input_line (FILE *f)
{
  int i = EOF;

  /* Recognize either LF or CR as a line terminator.  */




  last = first;
  while (last < bufsize && (i = getc (f)) != EOF && i != '\n' && i != '\r')
    buffer[last++] = i;

  if (i == EOF && errno != EINTR && last == first)
    return false;

  /* We didn't get the whole line because our buffer was too small.  */
  if (i != EOF && i != '\n' && i != '\r') {
    fprintf (stderr, "! Unable to read an entire line---bufsize=%u.\n",
                     (unsigned) bufsize);
    abort();
  }

  buffer[last] = ' ';
  if (last >= maxbufstack)
    maxbufstack = last;

  /* If next char is LF of a CRLF, read it.  */
  if (i == '\r') {
    while ((i = getc (f)) == EOF && errno == EINTR)
      ;
    if (i != '\n')
      ungetc (i, f);
  }
  
  
  while (last > first && buffer[last - 1] == ' ')
    --last;


  return true;
}


void
kpse_init_prog (const_string prefix,  unsigned dpi,
                const_string mode, const_string fallback)
{
 
}

boolean kpse_in_name_ok(const_string fname)
{

  return true;
}
boolean kpse_out_name_ok(const_string fname)
{

  return true;
}

void kpse_set_program_enabled(kpse_file_format_type fmt,
                                         boolean value, kpse_src_type level)
{
  //printf("Set Program Enable fmt %d val %d lev %d\n", fmt, value, level);
}

void kpse_set_program_name (const_string argv0,
                           const_string progname)
{
  
  //printf("Set Program name Argv %s progname %s\n", argv0, progname);
}

string kpse_find_glyph(const_string passed_fontname,  unsigned dpi, kpse_file_format_type format, void *notused)
{
	return NULL;
}

void kpse_reset_program_name (const_string progname)
{
 
  //printf("Reset Program name progname %s\n", progname);
}

#define MAXAVAILABLENAMESIZE 512
static int skpse_file_deamon_search(string name)
{
    int tmp_dgram_socket = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(tmp_dgram_socket <= 0)
    {
        printf("Unable to init a unix socket\n");
        return -1;
    }

    struct timeval tv;
    tv.tv_sec = 60;
    tv.tv_usec = 0;
    setsockopt(tmp_dgram_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

    struct sockaddr_un client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    snprintf(client_addr.sun_path, 64, "/tmp/pdftexc%d", getpid());
    unlink(client_addr.sun_path);

    if(bind(tmp_dgram_socket,  (struct sockaddr*) (&client_addr), (socklen_t) sizeof(client_addr)) == -1)
    {
        printf("Unable to send bind clientaddr \n");
        close(tmp_dgram_socket);
        return -2;
    }


    struct sockaddr_un server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    snprintf(server_addr.sun_path, 64, "/tmp/kpse_file_deamon");

    
  
    if(sendto(tmp_dgram_socket, name, strlen(name), 0, (struct sockaddr*) (&server_addr), (socklen_t) sizeof(server_addr)) ==-1)
    {
            printf("Unable to send the filedownload request\n");
            close(tmp_dgram_socket);
            unlink(client_addr.sun_path);
            return -4;
    }

     if(recv(tmp_dgram_socket, name, MAXAVAILABLENAMESIZE, 0) == -1)
     {
            printf("Unable to obtain the filedownload response\n");
            close(tmp_dgram_socket);
            unlink(client_addr.sun_path);
            return -3;
     }
     int res = 0;
     if(name[0] == 'n' && name[1] == 'o' && name[2] == 'n' && name[3] == 'e')
     {
        res = -1;
     }
     

     close(tmp_dgram_socket);
     unlink(client_addr.sun_path);
     //printf("return %d\n", res);
     return res;
}


string kpse_find_file(const_string name, kpse_file_format_type format,  boolean must_exist)
{
    if(name == NULL)
    {
      return NULL;
    }

    if(strlen(name) > 126)
    {
      printf("This file name is too long, skpse would not be able to handle it");
      return NULL;
    }

    string patched_name = malloc(MAXAVAILABLENAMESIZE);
    if(patched_name == NULL)
      return NULL;


    memset(patched_name, 0, 512);
    strcat(patched_name, name);
    
    if(name[0] == '/' || access(name, F_OK) != -1) //If it is absolute path or it is already exists based on the current directory, copy & return
    {
      
      return patched_name;
    }


   
    

    #define PREFIXPATH(path) //Todo if there is confusion, we can enforce matching the prefix
    #define SUFFIX(suf) \
    if(strrchr(patched_name, '.') == NULL) \
        strcat(patched_name, suf); \


    switch (format)
    { 
        case kpse_gf_format:
          PREFIXPATH("fonts/gf/");
          SUFFIX (".gf");
          break;
        case kpse_pk_format:
          PREFIXPATH("fonts/pk/");
          SUFFIX (".pk");
          break;
        case kpse_tfm_format:
          PREFIXPATH("fonts/tfm/");
          SUFFIX (".tfm");
          break;
        case kpse_afm_format:
          PREFIXPATH("fonts/atm/");
          SUFFIX (".afm");
          break;
        case kpse_base_format:
          SUFFIX (".base");
          break;
        case kpse_bib_format:
          PREFIXPATH("bibtex/bib/");
          SUFFIX (".bib");
          break;
        case kpse_bst_format:
          PREFIXPATH("bibtex/bst/");
          SUFFIX (".bst");
          break;
        case kpse_fontmap_format:
          PREFIXPATH("fonts/map/");
          SUFFIX (".map");
          break;
        case kpse_mem_format:
          SUFFIX (".mem");
          break;
        case kpse_mf_format:
          SUFFIX (".mf");
          break;
        case kpse_mft_format:
          PREFIXPATH("mft/")
          SUFFIX (".mft");
          break;
        case kpse_mfpool_format:
          SUFFIX (".pool");
          break;
        case kpse_mp_format:
          SUFFIX (".mp");
          break;
        case kpse_mppool_format:
          SUFFIX (".pool");
          break;
        case kpse_ocp_format:
          SUFFIX (".ocp");
          break;
        case kpse_ofm_format:
          SUFFIX (".ofm");
          break;
        case kpse_opl_format:
          SUFFIX (".opl");
          break;
        case kpse_otp_format:
          SUFFIX (".otp");
          break;
        case kpse_ovf_format:
          SUFFIX (".ovf");
          break;
        case kpse_ovp_format:
          SUFFIX (".ovp");
          break;
        case kpse_pict_format:
          SUFFIX (".esp");
          break;
        case kpse_tex_format:
          SUFFIX (".tex");
          break;
        case kpse_texpool_format:
          SUFFIX (".pool");
          break;
        case kpse_texsource_format:
          SUFFIX (".dtx");
          break;
        case kpse_type1_format:
          SUFFIX (".pfa");
          break;
        case kpse_vf_format:
          PREFIXPATH("fonts/vf/");
          SUFFIX (".vf");
          break;
        case kpse_ist_format:
          SUFFIX (".ist");
          break;
        case kpse_truetype_format:
          SUFFIX (".ttf");
          break;
        case kpse_type42_format:
          SUFFIX (".t42");
          break;
        case kpse_miscfonts_format:
          break;
        case kpse_enc_format:
          PREFIXPATH('fonts/enc/pdftex/');
          SUFFIX (".enc");
          break;
        case kpse_cmap_format:
          PREFIXPATH("fonts/cmap/");
          break;
        case kpse_sfd_format:
          SUFFIX (".sfd");
          break;
        case kpse_opentype_format:
          SUFFIX (".otf");
          break;
        case kpse_pdftex_config_format:
          break;
        case kpse_lig_format:
          SUFFIX (".lig");
          break;
        case kpse_texmfscripts_format:
          break;
        case kpse_fea_format:
          SUFFIX (".fea");
          break;
        case kpse_cid_format:
          SUFFIX (".cid");
          break;
        case kpse_mlbib_format:
          SUFFIX (".mlbib");
          break;
        case kpse_mlbst_format:
          SUFFIX (".mlbst");
          break;
        case kpse_ris_format:
          SUFFIX (".ris");
          break;
        case kpse_bltxml_format:
          SUFFIX (".bltxml");
          break;
        case kpse_fmt_format:
          SUFFIX (".fmt");
          break;
        default:
          printf("Unknown Kpse Format %d fixme\n", format);
          break;
  }

#undef SUFFIX
#undef PREFIXPATH
  //printf("I am looking for %s\n", patched_name);

  if(skpse_file_deamon_search(patched_name) == 0) //Nope Try download it //Now we can ask for help to download the file
  {
    return patched_name;
  }

  free(patched_name); //We try out bese, just leave it
  return NULL;
    
}


void xfseek (FILE *fp, long offset, int wherefrom, const_string filename)
{
	int ret = fseek(fp, offset, wherefrom);
	if(ret != 0)
	{
		fprintf(stderr, "File Seek Failed %s", filename);
		abort();
	}
	
}

long
xftell (FILE *f,  const_string filename)
{
    long where = ftell (f);

    if (where < 0)
    {
		fprintf(stderr, "File Tell Failed %s", filename);
		abort();
	}

    return where;
}


long
xftello (FILE *f,  const_string filename)
{
    long where = ftello (f);

    if (where < 0)
    {
		fprintf(stderr, "File Tello Failed %s", filename);
		abort();
	}

    return where;
}

void
xfseeko (FILE *f,  off_t offset,  int wherefrom,  const_string filename)
{
  if (fseeko (f, offset, wherefrom) != 0) {
        fprintf(stderr, "File fseeko Failed (%s %ld %d)", filename, offset, wherefrom);
		    abort();
  }
}

void do_undump (char *p, int item_size, int nitems, FILE *in_file)
{
	if (fread (p, item_size, nitems, in_file) != (size_t) nitems)
	{
		fprintf(stderr, "Could not undump %d %d-byte item(s) from %s",
            nitems, item_size, nameoffile+1);
		abort();
	}
}

void do_dump (char *p, int item_size, int nitems,  FILE *out_file)
{
	 if (fwrite (p, item_size, nitems, out_file) != nitems)
	 {
	 	fprintf (stderr, "! Could not write %d %d-byte item(s) to %s.\n",
               nitems, item_size, nameoffile+1);
	 	abort();
	 }
}

boolean
eof (FILE *file)
{
  register int c;

  /* If FILE doesn't exist, return true. This happens, for example,
     when a user does `mft foo.mf' -- there's no change file,
     so we never open it, so we end up calling this with a null pointer. */
  if (!file)
    return true;
    
  /* Maybe we're already at the end?  */
  if (feof (file))
    return true;

  if ((c = getc (file)) == EOF)
    return true;

  /* We weren't at the end.  Back up.  */
  (void) ungetc (c, file);

  return false;
}

integer
zround (double r)
{
  integer i;
  if (r > 2147483647.0)
    i = 2147483647;
  else if (r < -2147483647.0)
    i = -2147483647;
  else if (r >= 0.0)
    i = (integer)(r + 0.5);
  else
    i = (integer)(r - 0.5);

  return i;
}

string
xstrdup (const_string s)
{
  string new_string = (string)xmalloc(strlen (s) + 1);
  return strcpy(new_string, s);
}

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


#  define MAX_CSTRING_LEN     1024 * 1024
char *makecstring(integer s)
{
    static char *cstrbuf = NULL;
    char *p;
    static int allocsize;
    int allocgrow, i, l = strstart[s + 1] - strstart[s];
    if ((unsigned)(l + 1) > (unsigned)(MAX_CSTRING_LEN)){
    	fprintf(stderr, "buffer overflow at file %s, line %d", __FILE__,  __LINE__ ); abort();
    }
    
    if (cstrbuf == NULL) {
        allocsize = l + 1;
        cstrbuf = xmallocarray(char, allocsize);
    } else if (l + 1 > allocsize) {
        allocgrow = allocsize * 0.2;
        if (l + 1 - allocgrow > allocsize)
            allocsize = l + 1;
        else if (allocsize < MAX_CSTRING_LEN - allocgrow)
            allocsize += allocgrow;
        else
            allocsize = MAX_CSTRING_LEN;
        cstrbuf = xreallocarray(cstrbuf, char, allocsize);
    }
    p = cstrbuf;
    for (i = 0; i < l; i++)
        *p++ = strpool[i + strstart[s]];
    *p = 0;
    return cstrbuf;
}

 int runsystem(const char *noused)
{
	return 0;
}


void
topenin (void)
{
  
  buffer[first] = 0; 

  if (optind < ac)
  {
  	int k = first;
  	char *ptr = av[optind];
	while (*ptr) {
	        buffer[k++] = *(ptr++);
	}
    buffer[k++] = ' ';
    buffer[k] = 0;
  	ac = 0;
  	for (last = first; buffer[last]; ++last);
  }
}


void
get_seconds_and_micros (integer *seconds,  integer *micros)
{

  struct timeval tv;
  gettimeofday(&tv, NULL);
  *seconds = tv.tv_sec;
  *micros  = tv.tv_usec;


}


void maketimestr(char* time_str)
{
		time_t start_time = time((time_t *) NULL);
		struct tm lt;
		lt = *localtime(&start_time);
		size_t size = strftime(time_str, 31, "D:%Y%m%d%H%M%S", &lt);

		if (size == 0) {
	        time_str[0] = '\0';
	        return;
	    }

	    if (time_str[14] == '6') {
	        time_str[14] = '5';
	        time_str[15] = '9';
	        time_str[16] = '\0';    /* for safety */
	    }

	    time_str[size++] = 'Z';
	    time_str[size] = 0;
}

void initstarttime()
{
	if(start_time_str[0] == '\0')
	{
		maketimestr(start_time_str);
	}
}


void convertStringToHexString(const char *in, char *out, int lin)
{
    int i, j, k;
    char buf[3];
    j = 0;
    for (i = 0; i < lin; i++) {
        k = snprintf(buf, sizeof(buf),
                     "%02X", (unsigned int) (unsigned char) in[i]);
        out[j++] = buf[0];
        out[j++] = buf[1];
    }
    out[j] = '\0';
}


void
calledit (packedASCIIcode *filename,
          poolpointer fnstart,
          integer fnlength,
          integer linenumber)
{
  
  for (int i = 1; i <= inopen; i++)
    xfclose (inputfile[i], "inputfile");

  exit (1);
}

void
readtcxfile (void)
{

}

void
recorder_change_filename (string new_name)
{

}


void
get_date_and_time (integer *minutes,  integer *day,
                   integer *month,  integer *year)
{
  struct tm *tmptr;

    
    /* whether the envvar was not set (usual case) or invalid,
       use current time.  */
   time_t myclock = time ((time_t *) 0);
   tmptr = localtime (&myclock);

  

  *minutes = tmptr->tm_hour * 60 + tmptr->tm_min;
  *day = tmptr->tm_mday;
  *month = tmptr->tm_mon + 1;
  *year = tmptr->tm_year + 1900;
}




strnumber
getjobname(strnumber name)
{
    strnumber ret = name;
    if (c_job_name != NULL)
      ret = maketexstring(c_job_name);
    return ret;
}

strnumber
makefullnamestring(void)
{
  return maketexstring(fullnameoffile);
}

char *makecfilename(integer s)
{
    char *name = makecstring(s);
    char *p = name;
    char *q = name;

    while (*p) {
        if (*p != '"')
            *q++ = *p;
        p++;
    }
    *q = '\0';
    return name;
}


void getcreationdate(void)
{
    size_t len;

    initstarttime();
    /* put creation date on top of string pool and update poolptr */
    len = strlen(start_time_str);
    if ((unsigned) (poolptr + len) >= (unsigned) (poolsize)) {
        poolptr = poolsize;
        /* error by str_toks that calls str_room(1) */
        return;
    }
    memcpy(&strpool[poolptr], start_time_str, len);
    poolptr += len;
}


void getfilemoddate(integer s)
{
    struct stat file_data;

    const_string orig_name = makecfilename(s);

    char *file_name = kpse_find_tex(orig_name);
    if (file_name == NULL) {
        return;                 /* empty string */
    }
    if (! kpse_in_name_ok(file_name)) {
       return;                  /* no permission */
    }

    recorder_record_input(file_name);
    /* get file status */

    if (stat(file_name, &file_data) == 0) {

        size_t len;
        char time_str[32];
        maketimestr(time_str);
        len = strlen(time_str);
        if ((unsigned) (poolptr + len) >= (unsigned) (poolsize)) {
            poolptr = poolsize;
            /* error by str_toks that calls str_room(1) */
        } else {
            memcpy(&strpool[poolptr], time_str, len);
            poolptr += len;
        }
    }
    /* else { errno contains error code } */

    xfree(file_name);
}


void getfilesize(integer s)
{
    struct stat file_data;
    int i;


    char *file_name = kpse_find_tex(makecfilename(s));

    if (file_name == NULL) {
        return;                 /* empty string */
    }
    if (! kpse_in_name_ok(file_name)) {
       return;                  /* no permission */
    }

    recorder_record_input(file_name);
    /* get file status */

    if (stat(file_name, &file_data) == 0) {

        size_t len;
        char buf[20];
        /* st_size has type off_t */
        i = snprintf(buf, sizeof(buf),
                     "%lu", (long unsigned int) file_data.st_size);
        len = strlen(buf);
        if ((unsigned) (poolptr + len) >= (unsigned) (poolsize)) {
            poolptr = poolsize;
            /* error by str_toks that calls str_room(1) */
        } else {
            memcpy(&strpool[poolptr], buf, len);
            poolptr += len;
        }
    }
    /* else { errno contains error code } */

    xfree(file_name);
}


#define DIGEST_SIZE 16
#define FILE_BUF_SIZE 1024

void getmd5sum(strnumber s, boolean file)
{
    md5_state_t state;
    md5_byte_t digest[DIGEST_SIZE];
    char outbuf[2 * DIGEST_SIZE + 1];
    int len = 2 * DIGEST_SIZE;


    if (file) {
        char file_buf[FILE_BUF_SIZE];
        int read = 0;
        FILE *f;
        char *file_name;


        file_name = kpse_find_tex(makecfilename(s));

        if (file_name == NULL) {
            return;             /* empty string */
        }
        if (! kpse_in_name_ok(file_name)) {
           return;              /* no permission */
        }

        /* in case of error the empty string is returned,
           no need for xfopen that aborts on error.
         */
        f = fopen(file_name, FOPEN_RBIN_MODE);
        if (f == NULL) {
            xfree(file_name);
            return;
        }
        recorder_record_input(file_name);
        md5_init(&state);
        while ((read = fread(&file_buf, sizeof(char), FILE_BUF_SIZE, f)) > 0) {
            md5_append(&state, (const md5_byte_t *) file_buf, read);
        }
        md5_finish(&state, digest);
        fclose(f);

        xfree(file_name);
    } else {
        /* s contains the data */
        md5_init(&state);

        md5_append(&state,
                   (md5_byte_t *) &strpool[strstart[s]],
                   strstart[s + 1] - strstart[s]);
        md5_finish(&state, digest);
    }

    if (poolptr + len >= poolsize) {
        /* error by str_toks that calls str_room(1) */
        return;
    }
    convertStringToHexString((char *) digest, outbuf, DIGEST_SIZE);

    memcpy(&strpool[poolptr], outbuf, len);
    poolptr += len;

}


void getfiledump(integer s, int offset, int length)
{
    FILE *f;
    int read, i;
    poolpointer data_ptr;
    poolpointer data_end;
    char *file_name;

    if (length == 0) {
        /* empty result string */
        return;
    }

    if (poolptr + 2 * length + 1 >= poolsize) {
        /* no place for result */
        poolptr = poolsize;
        /* error by str_toks that calls str_room(1) */
        return;
    }


    file_name = kpse_find_tex(makecfilename(s));
    if (file_name == NULL) {
        return;                 /* empty string */
    }
    if (! kpse_in_name_ok(file_name)) {
       return;                  /* no permission */
    }

    /* read file data */
    f = fopen(file_name, FOPEN_RBIN_MODE);
    if (f == NULL) {
        xfree(file_name);
        return;
    }
    recorder_record_input(file_name);
    if (fseek(f, offset, SEEK_SET) != 0) {
        xfree(file_name);
        return;
    }

    /* there is enough space in the string pool, the read
       data are put in the upper half of the result, thus
       the conversion to hex can be done without overwriting
       unconverted bytes. */
    data_ptr = poolptr + length;
    read = fread(&strpool[data_ptr], sizeof(char), length, f);
    fclose(f);

    /* convert to hex */
    data_end = data_ptr + read;
    for (; data_ptr < data_end; data_ptr++) {
        i = snprintf((char *) &strpool[poolptr], 3,
                     "%.2X", (unsigned int) strpool[data_ptr]);

        poolptr += i;
    }

    xfree(file_name);
}


string
gettexstring (strnumber s)
{
  poolpointer len;
  string name;
  len = strstart[s + 1] - strstart[s];
  name = (string)xmalloc (len + 1);
  strncpy (name, (string)&strpool[strstart[s]], len);
  name[len] = 0;
  return name;
}

static int
compare_paths (const_string p1, const_string p2)
{
  int ret;
  while (
         (((ret = (*p1 - *p2)) == 0) && (*p2 != 0))

                || (IS_DIR_SEP(*p1) && IS_DIR_SEP(*p2))) {
       p1++, p2++;
  }
  ret = (ret < 0 ? -1 : (ret > 0 ? 1 : 0));
  return ret;
}

boolean
isnewsource (strnumber srcfilename, int lineno)
{
  char *name = gettexstring(srcfilename);
  return (compare_paths(name, last_source_name) != 0 || lineno != last_lineno);
}

void
remembersourceinfo (strnumber srcfilename, int lineno)
{
  if (last_source_name)
       free(last_source_name);
  last_source_name = gettexstring(srcfilename);
  last_lineno = lineno;
}

poolpointer
makesrcspecial (strnumber srcfilename, int lineno)
{
  poolpointer oldpoolptr = poolptr;
  char *filename = gettexstring(srcfilename);
  /* FIXME: Magic number. */
  char buf[40];
  char *s = buf;

  /* Always put a space after the number, which makes things easier
   * to parse.
   */
  sprintf (buf, "src:%d ", lineno);

  if (poolptr + strlen(buf) + strlen(filename) >= (size_t)poolsize) {
       fprintf (stderr, "\nstring pool overflow\n"); /* fixme */
       exit (1);
  }
  s = buf;
  while (*s)
    strpool[poolptr++] = *s++;

  s = filename;
  while (*s)
    strpool[poolptr++] = *s++;

  return (oldpoolptr);
}


int main(int argc, char**argv)
{
 ac = argc;
 av = argv;
 //Parse Argument
 int c;
 while ((c = getopt (argc, argv, "io:f:")) != -1)
    switch (c)
 {
      case 'i':
        iniversion = 1;
        break;
      case 'o':
        output_directory= optarg;
        break;
      case '?':
          fprintf (stderr,
                   "Usage: -i for iniversion, -o for output directory -f for inputfile\n");
        return 1;
      default:
        abort ();
  }



  //Now Basic Variable

 dumpname = DEFAULT_DUMP_NAME;
 int fmtstrlen = strlen(DEFAULT_FMT_NAME);
 TEXformatdefault = xmalloc(fmtstrlen + 2);
 memcpy(TEXformatdefault, DEFAULT_FMT_NAME, fmtstrlen);
 formatdefaultlength = strlen (TEXformatdefault + 1);
 interactionoption = 1;
 filelineerrorstylep = 0;
 parsefirstlinep = 0;

 //Go

  mainbody ();

  return EXIT_SUCCESS;
}