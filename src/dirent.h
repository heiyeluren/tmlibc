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
 * $Id: string.c 2008-11-16 16:01 heiyeluren $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>		/* flags for read and write */
#include <sys/types.h>	/* typedefs */
#include <sys/stat.h>	/* structure returned by stat */

#ifndef NAME_MAX
# define NAME_MAX 255	/* longest filename component; */
#endif

#ifndef DIRSIZ
# define DIRSIZ 255
#endif


/* system-dependent */
typedef struct {			/* portable directory entry */
	long ino;				/* inode number */
	char name[NAME_MAX+1];	/* name + '\0' terminator */
} Dirent;

typedef struct {			/* minimal DIR: no buffering, etc. */
	int fd;					/* file descriptor for the directory */
	Dirent d;				/* the directory entry */
} DIR;

struct direct {				/* directory entry */
	ino_t d_ino;			/* inode number */
	char d_name[DIRSIZ];	/* long name does not have '\0' */
};



/* function define */
#define dirfd(dir)				((dir)->fd)
#define rewinddir(dir)			(lseek((dir)->fd, 0, SEEK_SET))
#define seekdir(dir, offset)	(lseek((dir)->fd, offset, SEEK_SET))

DIR *opendir(const char *name);
DIR *fdopendir(int fd);
int closedir(DIR *dir);
struct dirent *readdir(DIR *dir);
int scandir(const char *dir, struct dirent ***namelist, int(*filter)(const struct dirent *), int(*compar)(const struct dirent **, const struct dirent **));


