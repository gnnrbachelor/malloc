#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

#define PG_SIZE 4096



typedef struct malloc_head
{
	size_t block;
	size_t size;
} header_m;

typedef struct block_data
{
	char *beg;
	char *end;
	size_t left_over;
	header_m cur;
	header_m next;
} b_data;

void *naive_malloc(size_t size);

#endif
