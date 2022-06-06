#include "malloc.h"

void *_calloc(size_t nmemb, size_t size)
{
	char *new_addr;

	new_addr = _malloc(nmemb * size);
	if (!new_addr)
		return (NULL);

	return (memset(new_addr, 0, nmemb * size));
}

