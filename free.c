#include "malloc.h"

void _free(void *ptr)
{
	header_m *block;

	if (!ptr)
		return;

	block = (header_m *)ptr;
	block--;

	block->size = 0;
}
