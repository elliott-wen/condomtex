#include <texmfmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
string fullnameoffile;
string output_directory;


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
recorder_change_filename (string new_name)
{

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


void
recorder_change_filename (string new_name)
{

}