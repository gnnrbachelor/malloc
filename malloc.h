#ifndef _MALLOC_H_
#define _MALLOC_H_

#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>

#define PG_SIZE 4096
#define M_HEAD_SIZE sizeof(header_m)



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
} b_data;

void *naive_malloc(size_t size);

#endif
