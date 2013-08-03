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

#include "stdlib.h"



/***************************************
 *
 *   String conversion function
 *
 ***************************************/


/**
 * atof - convert ASCII string to double
 *
 * @desc The function converts the initial portion of the string pointed to by nptr to double.  The behavior is
 the same as strtod(nptr, (char **) NULL);
 * @return The converted value
 */
double atof(const char *nptr){
    double val, power;
    int i, sign;
    const char *s = nptr;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++){
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }
    return sign * val / power;
}

/**
 * atoi - convert ASCII string to integer
 * 
 * @desc The function converts the initial portion of the string pointed to by nptr to int.  The behavior is the
 *       same as strtol(nptr, (char **) NULL, 10);
 * @return The converted value
 */
int atoi(const char *nptr){
    int i, n, sign;
    const char *s = nptr;

    for (i = 0; isspace(s[i]); i++) ;/* skip white space */
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') /* skip sign */
        i++;
    for (n = 0; isdigit(s[i]); i++)
        n = 10 * n + (s[i] - '0');
    return sign * n;
}

/**
 * atol - convert ASCII string to long integer
 *
 * @desc The function converts the initial portion of the string pointed to by nptr to int.  The behavior is the
 *       same as strtol(nptr, (char **) NULL, 10);
 * @return The converted value
 */
long atol(const char *nptr){
    long ret = 0L;
    int neg = 0;
    const char *s = nptr;

    while (s && *s && isspace(*s))
        s++;
    if (*s == '-' || *s == '+'){
        neg = *s == '-';
        s++;
    }
    for ( ; s && *s && isdigit (*s); s++)
        ret = (ret * 10) + (isdigit (*s) ? *s - '0' : *s);
    return (neg ? -ret : ret);
}


/**
 * strtod - convert ASCII string to floating point
 *
 * @desc The functions convert the initial portion of the string pointed to by nptr to double, float, and long double 
 *		 representation, respectively.
 * @return These functions return the converted value
 */
double strtod(char *str, char **ptr){
    char *p;
    //const char *str = nptr;
    //char **ptr = endptr;

    if (ptr == (char **)0)
        return atof (str);

    p = str;

    while (isspace (*p))
        ++p;

    if (*p == '+' || *p == '-')
        ++p;

    /* INF or INFINITY.  */
    if ((p[0] == 'i' || p[0] == 'I') && (p[1] == 'n' || p[1] == 'N') && (p[2] == 'f' || p[2] == 'F')){
        if ((p[3] == 'i' || p[3] == 'I') && (p[4] == 'n' || p[4] == 'N') && (p[5] == 'i' || p[5] == 'I') && (p[6] == 't' || p[6] == 'T') && (p[7] == 'y' || p[7] == 'Y')){
            *ptr = p + 7;
            return atof (str);
        } else {
            *ptr = p + 3;
            return atof (str);
        }
    }

    /* NAN or NAN(foo).  */
    if ((p[0] == 'n' || p[0] == 'N') && (p[1] == 'a' || p[1] == 'A') && (p[2] == 'n' || p[2] == 'N')){
        p += 3;
        if (*p == '('){
            ++p;
            while (*p != '\0' && *p != ')')
                ++p;
            if (*p == ')')
                ++p;
        }
        *ptr = p;
        return atof (str);
    }

    /* digits, with 0 or 1 periods in it.  */
    if (isdigit (*p) || *p == '.'){
        int got_dot = 0;
        while (isdigit (*p) || (!got_dot && *p == '.')){
            if (*p == '.')
                got_dot = 1;
            ++p;
        }

        /* Exponent.  */
        if (*p == 'e' || *p == 'E'){
            int i;
            i = 1;
            if (p[i] == '+' || p[i] == '-')
                ++i;
            if (isdigit (p[i])){
                while (isdigit (p[i]))
                    ++i;
                *ptr = p + i;
                return atof (str);
            }
        }
        *ptr = p;
        return atof (str);
    }
    /* Didn't find any digits.  Doesn't look like a number.  */
    *ptr = str;
    return 0.0;
}



/**
 * strtol - convert a string to a long integer
 *
 * @desc The function converts the initial part of the string in nptr to a long integer value according to the
 *       given base, which must be between 2 and 36 inclusive, or be the special value 0.
 * @return The function returns the result of the conversion, unless the value would underflow or overflow. If
 *         an underflow occurs, strtol() returns LONG_MIN.  If an overflow occurs, strtol()  returns  LONG_MAX.   In  both
 *         cases, errno is set to ERANGE.  Precisely the same holds for strtoll() (with LLONG_MIN and LLONG_MAX instead of
 *         LONG_MIN and LONG_MAX).
 */
long int strtol(const char *nptr, char **endptr, int base){
    const char *s = nptr;
    unsigned long acc;
    int c;
    unsigned long cutoff;
    int neg = 0, any, cutlim;

    /*
     * Skip white space and pick up leading +/- sign if any.
     * If base is 0, allow 0x for hex and 0 for octal, else
     * assume decimal; if base is already 16, allow 0x.
     */
    do {
        c = *s++;
    } while (isspace(c));
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) &&
            c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;

    /*
     * Compute the cutoff value between legal numbers and illegal
     * numbers.  That is the largest legal value, divided by the
     * base.  An input number that is greater than this value, if
     * followed by a legal input character, is too big.  One that
     * is equal to this value may be valid or not; the limit
     * between valid and invalid numbers is then based on the last
     * digit.  For instance, if the range for longs is
     * [-2147483648..2147483647] and the input base is 10,
     * cutoff will be set to 214748364 and cutlim to either
     * 7 (neg==0) or 8 (neg==1), meaning that if we have accumulated
     * a value > 214748364, or equal but the next digit is > 7 (or 8),
     * the number is too big, and we will return a range error.
     *
     * Set any if any `digits' consumed; make it negative to indicate
     * overflow.
     */
    cutoff = neg ? -(unsigned long)LONG_MIN : LONG_MAX;
    cutlim = cutoff % (unsigned long)base;
    cutoff /= (unsigned long)base;
    for (acc = 0, any = 0;; c = *s++) {
        if (isdigit(c))
            c -= '0';
        else if (isalpha(c))
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = neg ? LONG_MIN : LONG_MAX;
        errno = ERANGE;
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (char *) (any ? s - 1 : nptr);
    return (acc);
}


/**
 * strtoul - convert a string to an unsigned long integer
 *
 * @desc The function  converts  the  initial  part  of the string in nptr to an unsigned long integer value
 *       according to the given base, which must be between 2 and 36 inclusive, or be the special value 0
 * @return The function returns either the result of the conversion or, if there was a leading minus  sign, the
 *         negation  of  the  result of the conversion represented as an unsigned value, unless the original (non-negated)
 *         value would overflow; in the latter case, strtoul() returns ULONG_MAX and sets the  global  variable  errno  to
 *         ERANGE.  Precisely the same holds for strtoull() (with ULLONG_MAX instead of ULONG_MAX).
 */
unsigned long int strtoul(const char *nptr, char **endptr, int base){
    const char *s = nptr;
    unsigned long acc;
    int c;
    unsigned long cutoff;
    int neg = 0, any, cutlim;

    /*
     * See strtol for comments as to the logic used.
     */
    do {
        c = *s++;
    } while (isspace(c));
    if (c == '-') {
        neg = 1;
        c = *s++;
    } else if (c == '+')
        c = *s++;
    if ((base == 0 || base == 16) &&
            c == '0' && (*s == 'x' || *s == 'X')) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == '0' ? 8 : 10;
    cutoff = (unsigned long)ULONG_MAX / (unsigned long)base;
    cutlim = (unsigned long)ULONG_MAX % (unsigned long)base;
    for (acc = 0, any = 0;; c = *s++) {
        if (isdigit(c))
            c -= '0';
        else if (isalpha(c))
            c -= isupper(c) ? 'A' - 10 : 'a' - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || acc == cutoff && c > cutlim)
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = ULONG_MAX;
        errno = ERANGE;
    } else if (neg)
        acc = -acc;
    if (endptr != 0)
        *endptr = (char *) (any ? s - 1 : nptr);

    return (acc);
}



/***************************************
 *
 *    Math function
 *
 ***************************************/

/**
 * abs - compute the absolute value of an integer
 */
int abs(int j){
    return j < 0 ? -j : j;
}

/**
 * labs - compute the absolute value of an integer
 */
long int labs(long int j){
    return j < 0 ? -j : j;
}

/**
 * llabs - compute the absolute value of an integer
 */
long long int llabs(long long int j){
    return j < 0 ? -j : j;
}



/***************************************
 *
 * Data Structure and Algorithm function
 *
 ***************************************/

/**
 * bsearch - binary search of a sorted array
 *
 * @desc The function searches an array of nmemb objects, the initial member of which is pointed to by base, for a member 
 *		 that matches the object pointed to by key.  The size of each member of the array is specified by size
 * @return The function returns a pointer to a matching member of the array, or NULL if no match is  found. If there are 
 *		   multiple elements that match the key, the element returned is unspecified.
 */
void *bsearch (const void *key, const void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *)){
    size_t l, u, idx;
    const void *p;
    int comparison;

    l = 0;
    u = nmemb;
    while (l < u){
        idx = (l + u) / 2;
        p = (void *) (((const char *) base) + (idx * size));
        comparison = (*compar) (key, p);
        if (comparison < 0)
            u = idx;
        else if (comparison > 0)
            l = idx + 1;
        else
            return (void *) p;
    }

    return NULL;
}


/**
 * swap - swap two variables (for qsort)
 */
static void swap(void *base, size_t i, size_t j, size_t size){
    void *tmp = malloc(size);

    memcpy(tmp, (char *)base + i * size, size);
    memmove((char *)base + i * size, (char *)base + j * size, size);
    memcpy((char *)base + j * size, tmp, size);
    free(tmp);
}

/**
 * qsort - sorts an array
 *
 * @desc The function sorts an array with nmemb elements of size size.  The base argument points to the start of
 *		 the array
 * @return The function returns no value
 */
void qsort(void *base, size_t nmemb, size_t size, int (*compar) (const void *, const void *)){
    int i, last;

    if (nmemb <= 1)
        return;

    swap(base, 0, nmemb / 2, size);

    last = 0;
    for (i = 1; i < nmemb; i++)
        if (compar((char *)base + (i * size), base) < 0)
            swap(base, i, ++last, size);

    swap(base, 0, last, size);

    qsort(base, last, size, compar);
    qsort((char *)base + (last + 1) * size, nmemb - last - 1, size, compar);
}


/**
 * srand - pseudo-random number generator
 *
 * @desc The function sets its argument as the seed for a new sequence of pseudo-random integers to be returned
 *       by rand().  These sequences are repeatable by calling srand() with the same seed value.
 *       If no seed value is provided, the rand() function is automatically seeded with a value of 1
 * @return The function returns no value
 */
void srand(unsigned int seed){
    __rand_next__ = seed;
}


/**
 * rand - pseudo-random number generator
 *
 * @desc The function returns a pseudo-random integer between 0 and RAND_MAX.
 * @return The functions return a value between 0 and  RAND_MAX.
 */
int rand(void){
    __rand_next__ = __rand_next__ * 1103515245 + 12345;
    return (unsigned int)(__rand_next__ / 65536) % 32768;
}


/**
 * rand - pseudo-random number generator
 *
 * @desc The function is supplied with a pointer to an unsigned int, to be used as state. This is a very small amount of
 *       state, so this function will be a weak pseudo-random generator.
 * @return The functions return a value between 0 and  RAND_MAX.
 */
int rand_r(unsigned int *seed){
    unsigned int next = *seed;
    int result;

    next *= 1103515245;
    next += 12345;
    result = (unsigned int) (next / 65536) % 2048;

    next *= 1103515245;
    next += 12345;
    result <<= 10;
    result ^= (unsigned int) (next / 65536) % 1024;

    next *= 1103515245;
    next += 12345;
    result <<= 10;
    result ^= (unsigned int) (next / 65536) % 1024;

    *seed = next;

    return result;
}



/***************************************
 *
 *   Memory control function
 *
 ***************************************/

/**
 * morecore - ask system for more memory (for malloc)
 *
 * @desc system implement (like UNIX os use sbrk() alloc data segment)
 */
static Header *morecore(size_t nu){
    char *cp, *sbrk(int);
    Header *up;
    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));
    if (cp == (char *) -1) /* no space at all */
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    free((void *)(up+1));
    return freep;
}

/**
 * malloc - Allocate dynamic memory
 *
 * @desc malloc() allocates  size  bytes and returns a pointer to the allocated memory.  The memory is not cleared. If
 *       size is 0, then malloc() returns either NULL, or a unique pointer value that can later be  successfully  passed
 *       to free().
 * @return malloc(), the value returned is a pointer to the allocated memory, which is suitably aligned for any kind of 
 *		   variable, or NULL if the request fails.
 */
void *malloc(size_t size){
    size_t nbytes = size;
    Header *p, *prevp;
    size_t nunits;

    nunits = (nbytes+sizeof(Header)-1)/sizeof(header) + 1;
    if ((prevp = freep) == NULL) { /* no free list yet */
        base.s.ptr = freeptr = prevptr = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if (p->s.size >= nunits) { /* big enough */
            if (p->s.size == nunits) /* exactly */
                prevp->s.ptr = p->s.ptr;
            else { /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p+1);
        }
        if (p == freep) /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL)
                return NULL; /* none left */
    }
}

/**
 * free - Free dynamic memory
 *
 * @desc free()  frees the memory space pointed to by ptr, which must have been returned by a previous call to malloc(),
 *       calloc() or realloc().  Otherwise, or if free(ptr) has already been called before, undefined  behavior  occurs.
 *       If ptr is NULL, no operation is performed.
 * @return free() returns no value
 */
void free(void *ptr){
    Header *bp, *p;
    void *ap = ptr;

    bp = (Header *)ap - 1; /* point to block header */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* freed block at start or end of arena */
    if (bp + bp->size == p->s.ptr) { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->size == bp) { /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
}

/**
 * calloc - Allocate dynamic memory
 *
 * @desc calloc()  allocates memory for an array of nmemb elements of size bytes each and returns a pointer to the allo-
 *       cated memory.  The memory is set to zero.  If nmemb or size is 0, then  calloc()  returns  either  NULL,  or  a
 *       unique pointer value that can later be successfully passed to free().
 * @return the value returned is a pointer to the allocated memory, which is suitably aligned for any kind of variable, 
 *		   or NULL if the request fails.
 */
void *calloc(size_t nmemb, size_t size){
    void *ptr;

    ptr = malloc(nmemb * size);
    if (ptr)
        memset(ptr, '\0', nmemb * size);
    return ptr;
}


/**
 * realloc - Allocate dynamic memory
 *
 * @desc realloc() changes the size of the memory block pointed to by ptr to size bytes.  The contents will be unchanged
 *       to the minimum of the old and new sizes; newly allocated memory will be uninitialized.  If  ptr  is  NULL,  the
 *       call  is equivalent to malloc(size); if size is equal to zero, the call is equivalent to free(ptr).  Unless ptr
 *       is NULL, it must have been returned by an earlier call to malloc(), calloc() or realloc().  If the area pointed
 *       to was moved, a free(ptr) is done.
 * @return realloc() returns a pointer to the newly allocated memory, which is suitably aligned for any kind  of  variable
 *         and  may be different from ptr, or NULL if the request fails.  If size was equal to 0, either NULL or a pointer
 *         suitable to be passed to free() is returned.  If realloc() fails the original block is left  untouched;  it  is
 *         not freed or moved.
 */
void *realloc(void *ptr, size_t size){
    Header *bp;
    void *new_ptr;
    size_t old_size;

    if (ptr == NULL)
        return malloc(size);
    bp = (Header *)ptr - 1;     /* point to block header */
    old_size = sizeof(Header) * (bp->s.size - 1);
    new_ptr = malloc(size);
    if (new_ptr == NULL) {
        return NULL;
    }
    if (old_size <= size) {
        memcpy(new_ptr, ptr, old_size);
    } else {
        memcpy(new_ptr, ptr, size);
    }
    free(ptr);
    return new_ptr;
}



