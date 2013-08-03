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
 * $Id: string.c 2008-11-08 23:46 heiyeluren $
 */

#include "string.h"



/**
 * strlen - calculate the length of a string
 */
size_t strlen(const char *s){
    size_t n;

    for(n = 0; *s++; n++) ;
    return n;
}

/**
 * strcat - concatenate two strings
 */
char *strcat(char *dest, const char *src){
    char *ptr = dest;

    while( *dest++ ) ;
    for( *dest--; *dest++ = *src++; ) ;
    return ptr;
}

/**
 * stnrcat - concatenate two strings
 */
char *strncat(char *dest, const char *src, size_t n){
    char *ptr = dest;

    while( *dest++ );
    for( --dest; n-- && (*dest++ = *src++); ) ;
    *dest = 0; 
    return ptr;
}

/**
 * strcpy - copy a string
 */
char *strcpy(char *dest, const char *src){
    char *ptr = dest;

    while( *dest++ = *src++ ) ;
    *dest = 0;
    return ptr;
}

/**
 * strncpy - copy a string
 */
char *strncpy(char *dest, const char *src, size_t n){
    char *ptr = dest;

    while(n-- && (*dest++ = *src++)) ;
    *dest = 0;
    return ptr;
}

/**
 * strdup - duplicate a string
 * 
 * @return string pointer can be freed with free()
 */
char *strdup(const char *s){
    char *ptr, *dst;

    ptr = dst = (char *)malloc(strlen(s)+1);
    while(*dst++=*s++) ;
    *dst = 0;
    return ptr;
}

/**
 * strndup - duplicate a string
 *
 * @return string pointer can be freed with free()
 */
char *strndup(const char *s, size_t n){
    char *ptr, *dst;

    ptr = dst = (char *)malloc( strlen(s) + 1 );
    while(n-- && (*dst++ = *s++)) ;
    *dst = 0;
    return ptr;
}

/**
 * strcmp - compare two strings
 */
int strcmp(const char *s1, const char *s2){
    int s;

    while( (s = *s1++ - *s2++) == 0 ) ;
    return s;
}

/**
 * strcmp - compare two strings
 */
int strncmp(const char *s1, const char *s2, size_t n){
    int s;

    while( n-- && (s = *s1++ - *s2++) == 0 ) ;
    return s;
}

/** 
 * strcasecmp - compare two strings ignoring case
 */
int strcasecmp(const char *s1, const char *s2){
    char c1, c2;
    int s;

    for(;;){
        c1 = *s1++;
        c2 = *s2++;
        c1 = (c1>='A' && c1<='Z') ? c1 + ('a' - 'A') : c1;
        c2 = (c2>='A' && c2<='Z') ? c2 + ('a' - 'A') : c2;
        if ((s = c1 - c2) != 0) 
            break;
        if (c1==0 || c2==0){ 
            s = c1 - c2; 
            break; 
        }
    }
    return s;
}

/** 
 * strncasecmp - compare two strings ignoring case
 */
int strncasecmp(const char *s1, const char *s2, size_t n){
    int s;
    char c1, c2;

    while (n--){
        c1 = *s1++;
        c2 = *s2++;
        c1 = (c1>='A' && c1<='Z') ? c1 + ('a' - 'A') : c1;
        c2 = (c2>='A' && c2<='Z') ? c2 + ('a' - 'A') : c2;
        if ((s = c1 - c2) != 0) 
            break;
        if (c1==0 || c2==0){ 
            s = c1 - c2; 
            break; 
        }
    }
    return s;
}

/**
 * strcoll - compare two strings using the current locale
 */
int strcoll(const char *s1, const char *s2){
    //collate table (ASCII 0-255)
    unsigned char coll[256] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
        0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
        0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
        0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
        0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
        0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
    };

    while (coll[(unsigned char)*s1] == coll[(unsigned char)*s2]){
        if (*s1 == 0) return 0;
        s1++, s2++;
    }
    return coll[(unsigned char)*s1] - coll[(unsigned char)*s2];
}


/**
 * strchr - locate character in string
 *
 * @returns a pointer to the first occurrence of the character c in the string s
 */
char *strchr(const char *s, int c){
    for (; *s && *s != (char)c; s++) ;
    return ( *s == (char)c ? (char *)s : NULL );
}

/**
 * strrchr - locate character in string
 *
 * @returns a pointer to the last occurrence of the character c in the string s
 */
char *strrchr(const char *s, int c){
    size_t n;

    for ( n = 0; *s++; n++ ) ;
    for ( ; n != 0 && *s != (char)c; s--,n-- ) ;
    return ( *s == (char)c ? (char *)s : NULL );
}

/** 
 * index - locate character in string
 *
 * @returns a pointer to the first occurrence of the character c in the string s
 */
char *index(const char *s, int c){
    if ( (char)c == '\0'){
        while(*s++) ;    
        return (char *)s;
    }
    for ( ; *s && *s != (char)c; s++ ) ;
    return ( *s == (char)c ? (char *)s : NULL );
}

/** 
 * index - locate character in string
 *
 * @returns a pointer to the last occurrence of the character c in the string s
 */
char *rindex(const char *s, int c){
    size_t n;

    if ( (char)c == '\0'){
        while(*s++) ;    
        return (char *)s;
    }
    for ( n = 0; *s++; n++ ) ;
    for (; n != 0 && *s != (char)c; s--,n--) ;
    return ( *s == (char)c ? (char *)s : NULL );
}

/**
 * strpbrk - search a string for any of a set of characters
 *
 * @desc The function locates  the  first occurrence in the string s of any of the characters in 
 *		 the string accept.
 */
char *strpbrk(const char *s, const char *accept){
	const char *s1, *s2;

	for (s1 = s; *s1; s1++){
		for (s2 = accept; *s2; s2++){
			if (*s1 == *s2){
				return (char *)s1;
			}
		}
	}
	return NULL;
}

/**
 * strspn - search a string for a set of characters
 *
 * @desc The function calculates the length of the initial segment of s which consists entirely of 
 *		 characters in accept.
 */
size_t strspn(const char *s, const char * accept){
	const char *s1, *s2;
	short flag;
	size_t n;


	for (n = 0,s1 = s; *s1; s1++){
		flag = 0;
		for (s2 = accept; *s2; s2++){
			if (*s1 == *s2){
				++n, flag = 1;
			}
		}
		if (!flag) break;
	}
	return n;
}

/**
 * strcspn - search a string for a set of characters
 *
 * @desc The function calculates the length of the initial segment of s which consists entirely of 
 *		 characters not in reject.
 */
size_t strcspn(const char *s, const char *reject){
	const char *s1, *s2;
	short flag;
	size_t n;

	for (n = 0, s1 = s; *s1; s1++){
		flag = 0;
		for (s2 = reject; *s2; s2++){
			if (*s1 == *s2){
				flag = 1;
			}
		}
		if (flag) break;
		n++;
	}
	return n;
}

/**
 * strstr - locate a substring
 *
 * @desc The function finds the first occurrence of the substring needle in the string haystack.  
 *		 The terminat-ing '\0' characters are not compared.
 */

char *strstr(const char *haystack, const char *needle){
	const char *s1, *s2;
	size_t n, len;

	for (len = 0, s2 = needle; *s2++; ++len) ;
	for (s1 = haystack; *s1; s1++){
		for (n = 0, s2 = needle; *s2 && *s1 == *s2; s1++, s2++, n++) ;
		if (len == n) return (char *)s1;
	}
	return NULL;
}

/** 
 * strtok - extract tokens from strings
 *
 * @return The functions return a pointer to the next token, or NULL if there are no more tokens.
 */
char *strtok(char *str, const char *delim){
    static char *tok;

    if (str == NULL) str = tok;
    str += strspn(str, delim);
    if (*str == '\0') return NULL;
    tok = str + strcspn(str, delim);
    if (*tok != '\0') *(tok)++ = '\0';
    return str;
}

/**
 * memcpy - copy memory area
 *
 * @desc The function copies n bytes from memory area src to memory area dest.  The memory areas should not
 *       overlap.  Use memmove(3) if the memory areas do overlap.
 * @return The function returns a pointer to dest.
 */
void *memcpy(void *dest, const void *src, size_t n){
	char *s1, *s2;
	for (s1 = (char *)dest, s2 = (char *)src; n--;){
		*s1++ = *s2++;
	}
	return (void *)dest;
}

/**
 * memccpy - copy memory area
 *
 * @desc The function copies no more than n bytes from memory area src to memory area dest, stopping when the
 *       character c is found.
 * @return The function returns a pointer to dest.
 */
void *memccpy(void *dest, const void *src, int c, size_t n){
	char *s1, *s2;
	for (s1 = (char *)dest, s2 = (char *)src; n--;){
		if ((*s1++ = *s2++) == (char)c){
			return (void *)s1;
		}
	}
	return NULL;
}

/**
 * memmove - copy memory area
 *
 * @desc The function copies n bytes from memory area src to memory area dest. The memory areas may overlap:
 *       copying takes place as though the bytes in src are first copied into a temporary array that does not overlap
 *       src or dst, and the bytes are then copied from the temporary array to dest.
 * @return The function returns a pointer to dest.
 */
void *memmove(void *dest, const void *src, size_t n){
    size_t i;

    if (src >= dest || (void *)((char *)src + n) <= dest) {
        return memcpy(dest, src, n);
    } else {
        for (i = n; i > 0; i--) {
            ((char *)dest)[i - 1] = ((const char *)src)[i - 1];
        }
        return dest;
    }
}


/**
 * memset - fill memory with a constant byte
 *
 * @desc The function fills the first n bytes of the memory area pointed to by s with the constant byte c.
 * @return The function returns a pointer to the memory area s.
 */
void *memset(void *s , int c, size_t n){
	unsigned char *mem = s;
	while (n--){
		*mem++ = (unsigned char)c;
	}
	return (void *)s;
}

/**
 * memcmp - compare memory areas
 * 
 * @desc The function compares the first n bytes of the memory areas s1 and s2. It returns an integer less
 *       than,equal to, or greater than zero if s1 is found, respectively, to be less than, to  match, or be greater
 *       than s2.
 * @return The function returns an integer less than, equal to, or greater than zero if the first n bytes of s1
 *         is found, respectively, to be less than, to match, or be greater than the first n bytes of s2. 
 */
int memcmp(const void *s1, const void *s2, size_t n){
	const char *ts1, *ts2;
	for (ts1 = (char *)s1, ts2 = (char *)s2; --n && (*ts1 == *ts2); ts1++, ts2++) ;
	return (*ts1 - *ts2);
}

/**
 * memchr - scan memory for a character
 *
 * @desc The function scans the first n bytes of the memory area pointed to by s for the character c.  The
 *       first byte to match c (interpreted as an unsigned character) stops the operation.
 * @return The functions return a pointer to the matching byte or NULL if the character does not occur in 
 *		   the given memory area.
 */
void *memchr(const void *s, int c, size_t n){
	const char *s1 = s;
	while (n--){
		if ((*s1++ == (char)c)){
			return (void *)s1;
		}
	}
	return NULL;
}

/**
 * memrchr - scan memory for a character
 *
 * @desc The function is like the function, except that it searches backwards from the end of  the  n
 *       bytes pointed to by s instead of forwards from the front.
 * @return The functions return a pointer to the matching byte or NULL if the character does not occur in 
 *		   the given memory area.
 */
void *memrchr(const void *s, int c, size_t n){
	const char *s1;
	for (s1 = s, s1 += n; n--;){
		if ((*s1-- == (char)c)){
			return (void *)s1;
		}
	}
	return NULL;
}

/**
 * bzero - write zero-valued bytes
 *
 * @desc The function sets the first n bytes of the byte area starting at s to zero (bytes containing '\0').
 */
void bzero(void *s, int n){
	memset((void *)s, 0, (size_t)n);
}

/** 
 * bcopy - copy byte sequence
 * 
 * @desc The function copies n bytes from src to dest.  The result is correct, even when both areas overlap.
 */
void bcopy(const void *src, void *dest, int n){
	memcpy((void *)dest, (void *)src, (size_t)n);
}

/**
 * bcmp - compare byte sequences
 *
 * @desc The function compares the two byte sequences s1 and s2 of length n each.  If they are equal, and in 
 *		 particular if n is zero, bcmp() returns 0.  Otherwise it returns a non-zero result.
 * @return The function returns 0 if the byte sequences are equal, otherwise a non-zero result is returned.
 */
int bcmp(const void *s1, const void *s2, int n){
	return memcmp((void *)s1, (void *)s2, (size_t)n);
}


