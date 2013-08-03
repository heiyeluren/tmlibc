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
 * $Id: string.c 2008-11-19 03:04 heiyeluren $
 */

#include <sys/types.h>
//#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <fcntl.h>
#include<unistd.h>

#ifndef STDIN_FILENO
#define STDIN_FILENO	0
#endif
#ifndef STDOUT_FILENO
#define STDOUT_FILENO	1
#endif
#ifndef STDERR_FILENO
#define STDERR_FILENO	2
#endif

#ifndef _STDIO_H
# define _STDIO_H   1
#endif

#define __UNGET_SIZE 10

#define NULL		0
#define EOF			(-1)
#define BUFSIZ		1024
#define OPEN_MAX	37	/* max #files open at once */
#define PERMS		0666/* RW for owner, group, others */

/* file position operate const */
#define SEEK_SET    0   /* Seek from beginning of file.  */
#define SEEK_CUR    1   /* Seek from current position.  */
#define SEEK_END    2   /* Seek from end of file.  */

/* standard io buffer flag */
#define _IOFBF		0	/* fully buffered */
#define _IOLBF		1	/* line buffered */
#define _IONBF		2	/* unbuffered */

/* file operate mode & flag */
enum _flags {
	_READ	= 01,	/* file open for reading */
	_WRITE	= 02,	/* file open for writing */
	_UNBUF	= 04,	/* file is unbuffered */
	_EOF	= 010,	/* EOF has occurred on this file */
	_ERR	= 020	/* error occurred on this file */
};

/* file stream struct pointer */
typedef struct _iobuf {
	int cnt;		/* characters left */
	char *ptr;		/* next character position */
	char *base;		/* location of buffer */
	int flag;		/* mode of file access */
	int fd;			/* file descriptor */
	long pos;		/* pointer current position */
	//int err;		/* error flag */
} FILE;

/* default: standard input, standard output, stander error */
FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
	{ 0, (char *) 0, (char *) 0, _READ,			   STDIN_FILENO,  0 },
	{ 0, (char *) 0, (char *) 0, _WRITE,		   STDOUT_FILENO, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, | _UNBUF, STDERR_FILENO, 0 }
};
//extern FILE _iob[OPEN_MAX];
#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

/* internal function define */
int _fillbuf(FILE *fp);
int _flushbuf(int x, FILE *fp);

/* external function define */
void setbuf(FILE *stream, char *buf);
void setbuffer(FILE *stream, char *buf, size_t size);
void setlinebuf(FILE *stream);
int setvbuf(FILE *stream, char *buf, int mode , size_t size);
int fflush(FILE *stream);
int fpurge(FILE *stream);
void clearerr(FILE * stream);

int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);

FILE *fopen(const char *path, const char *mode);
FILE *fdopen(int fildes, const char *mode);
FILE *freopen(const char *path, const char *mode, FILE *stream);
int fclose(FILE *fp);

int ungetc(int c, FILE *stream);
int fgetc(FILE *stream);
char *fgets(char *s, int size, FILE *stream);
char *gets(char *s);
int fputc(int c, FILE * stream);
int fputs(const char * s, FILE * stream);
int puts(const char *s);


size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb,FILE *stream);


/* inline function */
#define feof(p)		((p)->flag & _EOF) != 0)
#define ferror(p)	((p)->flag & _ERR) != 0)
#define fileno(p)	((p)->fd)
#define getc(p)		(--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p)	(--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#define getchar()	getc(stdin)
#define putchar(x)	putc((x), stdout)
#define ftell(p)	((p)->pos)
#define rewind(p)	(lseek((p)->fd, 0, SEEK_SET)&&((p)->pos = 0))
#define clearerr(p)	((p)->flag = (p)->flag^((p)->flag&_ERR))


