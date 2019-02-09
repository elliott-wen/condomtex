#define	EXTERN /* Instantiate data from pdftexd.h here.  */
#define DLLPROC dllpdftexmain
#include <pdftexd.h>
string fullnameoffile;
string output_directory;
int tfmtemp;
int texinputtype;
int kpse_make_tex_discard_errors;
string translate_filename;
string version_string = "pdfTeX Standalone 0.1 beta";
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

int main()
{
	return 0;
}


void *xmalloc(size_t newsize)
{
	void *ptr = malloc(newsize);
	if(!ptr)
	{
		fprintf(stderr, "Malloc Failed");
		abort();
	}
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

        fprintf(stderr, "File Open Failed %s", filename);
        abort();
    }

    return f;
}





int xfclose ( FILE * stream )
{
	int ret = fclose(stream);	
	if(ret != 0)
	{
		fprintf(stderr, "File Close Failed");
		abort();
	}
	return 0;
}

void
close_file (FILE *f)
{
  if (!f)
    return;
  xfclose(f);
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


   
    

    #define PREFIX(path) //Todo if there is confusion, we can enforce matching the prefix
    #define SUFFIX(suf) \
    if(strrchr(patched_name, '.') == NULL) \
        strcat(patched_name, suf); \


    switch (format)
    { 
        case kpse_gf_format:
          PREFIX("fonts/gf/");
          SUFFIX (".gf");
          break;
        case kpse_pk_format:
          PREFIX("fonts/pk/");
          SUFFIX (".pk");
          break;
        case kpse_tfm_format:
          PREFIX("fonts/tfm/");
          SUFFIX (".tfm");
          break;
        case kpse_afm_format:
          PREFIX("fonts/atm/");
          SUFFIX (".afm");
          break;
        case kpse_base_format:
          SUFFIX (".base");
          break;
        case kpse_bib_format:
          PREFIX("bibtex/bib/");
          SUFFIX (".bib");
          break;
        case kpse_bst_format:
          PREFIX("bibtex/bst/");
          SUFFIX (".bst");
          break;
        case kpse_fontmap_format:
          PREFIX("fonts/map/");
          SUFFIX (".map");
          break;
        case kpse_mem_format:
          SUFFIX (".mem");
          break;
        case kpse_mf_format:
          SUFFIX (".mf");
          break;
        case kpse_mft_format:
          PREFIX("mft/")
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
          PREFIX("fonts/vf/");
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
          PREFIX('fonts/enc/pdftex/');
          SUFFIX (".enc");
          break;
        case kpse_cmap_format:
          PREFIX("fonts/cmap/");
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
#undef PREFIX
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
        fprintf(stderr, "File fseeko Failed %s", filename);
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

