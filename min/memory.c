#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <texmfmp.h>

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

