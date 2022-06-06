#include "malloc.h"

static b_data control;
header_m *cur, *next;


size_t align(size_t size)
{
	size += 8 - size % 8;
	return (size);
}

char *get_next(char *new_addr, size_t n_size)
{
	while (new_addr < control.end)
	{
		cur = (header_m *)new_addr;
		if (cur->size == 0)
			break;
		if (cur->block - cur->size >= n_size)
		{
			next = (header_m *)(new_addr + cur->size + HDR_SZ);
			next->block = cur->block - cur->size - HDR_SZ;
			cur->block = cur->size;
			new_addr = (char *)next;
			break;
		}
		new_addr += HDR_SZ + cur->block;
	}
	return (new_addr);

}

void calc_pg(char *new_addr, size_t n_size)
{
	if (new_addr == control.end)
	{
		while (control.left_over < n_size + HDR_SZ)
		{
			if (sbrk(PG_SIZE) == (void *)-1)
				return;
			control.left_over += PG_SIZE;
		}
		cur->block = n_size;
		control.end = new_addr + n_size + HDR_SZ;
		control.left_over = control.left_over - n_size - HDR_SZ;
	}

}

void *_malloc(size_t size)
{
	size_t n_size = align(size);
	char *new_addr;

	if (control.beg == NULL)
	{
		control.beg = sbrk(0);
		control.end = control.beg;
	}

	new_addr = control.beg;

	new_addr = get_next(new_addr, n_size);

	cur = (header_m *)new_addr;
	calc_pg(new_addr, n_size);
	cur->size = n_size;

	return (new_addr + HDR_SZ);
}

