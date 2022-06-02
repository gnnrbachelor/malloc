#include "malloc.h"

static b_data control;
size_t header_sz = sizeof(header_m);

size_t align(size_t size)
{
	size += 8 - size % 8;
	return (size);
}

void calc_break(size_t n_size)
{
	while (control.left_over < n_size + header_sz)
	{
		if (sbrk(PG_SIZE) == (void *)-1)
			return;
		control.left_over += PG_SIZE;
	}
}

char *check_end(char *new_addr)
{
	while (new_addr != control.end)
		new_addr += header_sz + *(size_t *)new_addr;
	if (new_addr == control.end)
	{
		new_addr += header_sz + *(size_t *)new_addr;
		control.end = new_addr;
	}
	return (new_addr);
}


void *naive_malloc(size_t size)
{
	size_t n_size;
	char *new_addr;

	if (control.beg == NULL)
		control.beg = sbrk(0);

	n_size = align(size);

	calc_break(n_size);

	new_addr = control.beg;

	if (control.end)
		new_addr = check_end(new_addr);
	else
		control.end = new_addr;

	*(size_t*)new_addr = n_size;
	return (new_addr + header_sz);
}
