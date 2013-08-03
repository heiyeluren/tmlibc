/**
 * Tima Standard ANSI C based Library
 *
 * Copyright (C) 2008 heiyeluren. All rights reserved.
 *
 * Open-source ANSI C library powered by  TieMa(TIMA) Studio.
 *  
 * Use and distribution licensed under the BSD license.  See
 * the LICENSE file for full text.
 *
 * To learn more open-source code, http://heiyeluren.googlecode.com
 * My blog: http://blog.csdn.net/heiyeshuwu
 *
 * $Id: stdlib.c 2008-11-09 23:31 heiyeluren $
 */

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>


/**
 * for string conversion function 
 */
#ifndef ULONG_MAX
#define	ULONG_MAX	((unsigned long)(~0L))		/* 0xFFFFFFFF */
#endif

#ifndef LONG_MAX
#define	LONG_MAX	((long)(ULONG_MAX >> 1))	/* 0x7FFFFFFF */
#endif

#ifndef LONG_MIN
#define	LONG_MIN	((long)(~LONG_MAX))		/* 0x80000000 */
#endif

/**
 * for rand & srand seed 
 */
#ifndef RAND_MAX
#define RAND_MAX	1103515245
#endif

unsigned long int __rand_next__ = 1;

/**
 * for memory control function 
 */
#define NALLOC 1024 /* minimum #units to request */

typedef long Align; /* for alignment to long boundary */
union header { /* block header */
    struct {
        union header *ptr; /* next block if on free list */
        size_t size; /* size of this block */
    } s;
    Align x; /* force alignment of blocks */
};
typedef union header Header;

static Header base; /* empty list to get started */
static Header *freep = NULL; /* start of free list */


/**
 * String conversion function define
 */
double atof(const char *nptr);
int atoi(const char *nptr);
long atol(const char *nptr);
//double strtod(const char *nptr, char **endptr);
double strtod(char *str, char **ptr);
long int strtol(const char *nptr, char **endptr,int base);
unsigned long int strtoul(const char *nptr, char **endptr, int base);


/**
 * Math function define
 */
int abs(int j);
long int labs(long int j);
long long int llabs(long long int j);


/**
 * Data Structure and Algorithm function define
 */
void *bsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar) (const void*, const void*));
void qsort(void * base, size_t nmemb,size_t size, int ( * compar)(const void *, const void *));
void srand(unsigned int seed);
int rand(void);
int rand_r(unsigned int *seed);


/**
 * Memory control function define
 */
void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);



