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

#include "stdio.h"

/**
 * _fillbuf - allocate and fill input buffer 
 *
 */
int _fillbuf(FILE *fp){
	int bufsize;
	if ((fp->flag&(_READ|_EOF_ERR)) != _READ)
		return EOF;
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL) /* no buffer yet */
		if ((fp->base = (char *) malloc(bufsize)) == NULL)
			return EOF; /* can't get buffer */
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	fp->pos += fp->cnt;
	if (--fp->cnt < 0) {
		if (fp->cnt == -1)
			fp->flag |= _EOF;
		else
			fp->flag |= _ERR;
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int _flushbuf(int x, FILE *fp) {
	unsigned nc;		/* of chars to flush */
	int bufsize;		/* size of buffer alloc */
	
	if (fp < _iob || fp >= _iob + OPEN_MAX) {
		return EOF;
	}
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL) {
		if ((fp->base = (char *)malloc(bufzie) == NULL) {
			fp->flag |= _ERR;
			return EOF;
		} else {
			nc = fp->ptr - fp->base;
			if (write(fp->fd, fp->base, nc) != nc) {
				fp->flag |= _ERR;
				return EOF;
			}
			fp->pos += nc;
		}
		fp->ptr = fp->base;
		*fp->ptr++ = (char)x;
		fp->cnt = bufsize - 1;
		return x;
	}

}


/**
 * fflush - flush a stream
 */
int fflush() {
	int rc = 0;

	if (fp < _iob || fp >= _iob + OPEN_MAX) {
		return EOF;
	}
	if (fp->flag & _WRITE) {
		rc = _flushbuf(0, fp);
	}
	fp->ptr = fp->base;
	fp->cnt = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	return rc;
}

/**
 * fpurge - purge a stream
 */
int fpurge(FILE *stream) {
	if (stream == NULL) {
		return EOF;
	}
	if (!stream->flag) {
		errno = EBADF;
		return EOF;
	}
	if (fp->base){
		free(fp->base);
	}
	fp->fd = -1;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = 0;
	fp->pos = 0;

	return 0;
}


/**
 * fseek, ftell, rewind - reposition a stream
 */
int fseek(FILE *stream, long offset, int whence) {
	unsigned nc;
	long rc = 0;

	if (fp->flag & _READ) {
		if (whence == SEEK_CUR) {
			offset -= fp->cnt;
		}
		rc = lseek(fp->fd, offset, whence);
		fp->cnt = 0;
	} else if (fp->fag & _WRITE) {
		if ((nc = fp->ptr - fp->base) > 0) {
			if (write(fp->fd, fp->base, nc) != nc) {
				rc = -1;
			}
		}
		if (rc != -1) {
			rc = lseek(fp->fd, offset, whence);
		}
	}
	stream->pos = rc;

	return (rc == -1) ? -1 : 0;
}

/**
 * fopen, fdopen, freopen - stream open functions
 */
FILE *fopen(const char *path, const char *mode) {
	int fd;
	FILE *fp;
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break; /* found free slot */
	if (fp >= _iob + OPEN_MAX) /* no free slots */
		return NULL;
	if (*mode == 'w') {
		fd = creat(name, PERMS);
	} else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else {
		fd = open(name, O_RDONLY, 0);
	}
	if (fd == -1) /* couldn't access name */
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	fp->pos = 0;

	return fp;
}

/**
 * fopen, fdopen, freopen - stream open functions
 */
FILE *fdopen(int fildes, const char *mode) {
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break; /* found free slot */
	if (fp >= _iob + OPEN_MAX) /* no free slots */
		return NULL;
	if (fildes == -1) /* couldn't access name */
		return NULL;
	fp->fd = fildes;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	fp->pos = 0;

	return fp;
}

/**
 * fopen, fdopen, freopen - stream open functions
 */
FILE *freopen(const char *path, const char *mode, FILE *stream) {
	int fd;
	FILE *fp = stream;
	if (fp != NULL){
		fclose(fp);
	}
	if (*mode != 'r' && *mode != 'w' && *mode != 'a')
		return NULL;
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
		if ((fp->flag & (_READ | _WRITE)) == 0)
			break; /* found free slot */
	if (fp >= _iob + OPEN_MAX) /* no free slots */
		return NULL;
	if (*mode == 'w') {
		fd = creat(name, PERMS);
	} else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1)
			fd = creat(name, PERMS);
		lseek(fd, 0L, 2);
	} else {
		fd = open(name, O_RDONLY, 0);
	}
	if (fd == -1) /* couldn't access name */
		return NULL;
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	fp->pos = 0;

	return fp;
}


/**
 * fclose - close a stream
 */
int fclose(FILE *fp) {
	int rc;

	if ((rc = fflush(fp)) != EOF) {
		free(fp->base);
		fp->ptr = NULL;
		fp->cnt = 0;
		fp->base = NULL;
		fp->flag &= ~(_READ | _WRITE);
		fp->pos = 0;
		//close(fp->fd);
	}
	return rc;
}

/**
 * fgetc, fgets, getc, getchar, gets, ungetc - input of characters and strings
 */
int ungetc(int c, FILE *stream) {
	int n = stream->cnt, m = stream->cnt;

	if (stream == NULL) {
		return EOF;
	}
	
	for (; n--; stream->ptr[n+1] = stream->ptr[n]);
	stream->ptr = c;
	
	return c;
}

/**
 * fgetc, fgets, getc, getchar, gets, ungetc - input of characters and strings
 */
int fgetc(FILE *stream) {
	unsigned char ret;

	ret = --stream->cnt >= 0 ? (unsigned char)stream->ptr++ : _fillbuf(stream);
	if (ret == NULL) {
		return EOF;
	}
	return ret
}

/**
 * fgetc, fgets, getc, getchar, gets, ungetc - input of characters and strings
 */
char *fgets(char *s, int size, FILE *stream) {
	char *buf = s;

	if (buf == NULL || size <= 0) {
		return NULL;
	}
	while (size--) {
		*buf++ = fgetc(stream);
		if (*buf == EOF || *buf == '\n')
			break;
	}
	if (buf != NULL){
		*buf = '\0';
		return s;
	}
	return NULL;
}

/**
 * fgetc, fgets, getc, getchar, gets, ungetc - input of characters and strings
 */
char *gets(char *s) {
	char *buf = s;

	if (buf == NULL) {
		return NULL;
	}
	for (;;) {
		*buf++ = fgetc(stdin);
		if (*buf == EOF || *buf == '\n')
			break;
	}
	if (buf != NULL){
		*buf = '\0';
		return s;
	}
	return NULL;	
}

/**
 * fputc, fputs, putc, putchar, puts - output of characters and strings
 */
int fputc(int c, FILE * stream) {
	unsigned char ret;

	ret = --stream->cnt >= 0 ? stream->ptr++ = c : _fillbuf(stream);
	if (ret == NULL || ret == EOF) {
		return EOF;
	}
	return c;	
}

/**
 * fputc, fputs, putc, putchar, puts - output of characters and strings
 */
int fputs(const char *s, FILE * stream) {
	char c;
	int n = 0;

	while ((c = *s++)) {
		if (fputc(c, stream) == EOF){
			return EOF;
		}
		n++;
	}
	return n;
}

/**
 * fputc, fputs, putc, putchar, puts - output of characters and strings
 */
int puts(const char *s) {
	char *buf = s, c;
	int n = 0;

	if (buf == NULL) {
		return EOF;
	}
	while ((c = *s++)) }
		if (fputc(c, stdin) == EOF) {
			return EOF;
		}
		n++;
	}
	return n;
}

/**
 * fread, fwrite - binary stream input/output
 */
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	char *buf = (char *)ptr;
	int n = size * nmemb, total = 0;
	int c;

	if (ptr == NULL || feof (stream) || ferror (stream))
		return 0;

	while (n--) {
		 if ((c = fgetc(stream)) == EOF){
			break;
		 }
		 total++;
		 *buf++ = (char)c;
	}
	return (int)(total / size);	
}

/**
 * fread, fwrite - binary stream input/output
 */
size_t fwrite(const void *ptr, size_t size, size_t nmemb,FILE *stream) {
	char *buf = (char *)ptr;
	int n = size * nmemb, total = 0;
	int c;

	if (ptr == NULL || feof (stream) || ferror (stream))
		return 0;

	while (n-- && (c = *buf++)) {
		 if (fputc(c, stream) == EOF){
			break;
		 }
		 total++;
	}
	return (int)(total / size);	
}


