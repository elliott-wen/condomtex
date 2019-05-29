#include "texmfmp.h"

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
