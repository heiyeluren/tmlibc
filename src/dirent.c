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

#include "dirent.h"


/**
 * opendir - open a directory
 *
 * @desc The  opendir()  function  opens  a directory stream corre-
 *       sponding to the directory name, and returns a  pointer  to
 *       the  directory  stream.   The  stream is positioned at the
 *       first entry in the directory.
 *@return The opendir() function returns a pointer to the  directory
 *        stream or NULL if an error occurred.
 */
DIR *opendir(char *dirname){
	int fd;
	struct stat stbuf;
	DIR *dp;
	if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}

/**
 * fdopendir ¨C open directory
 *
 * @desc The fdopendir() function opens a directory stream for the directory 
 *       file descriptor fildes. The directory file descriptor should not be 
 *       used or closed following a successful function call, as this might 
 *       cause undefined results from future operations on the directory stream 
 *       obtained from the call. Use closedir(3C) to close a directory stream.
 * @return fdopendir() return a pointer to an object of type DIR. Otherwise, 
 *         a null pointer is returned and errno is set to indicate the error.
 */
DIR *fdopendir(int fd){
	struct stat stbuf;
	if ((fd = -1 || fstat(fd, &stbuf) == -1	|| (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (DIR *) malloc(sizeof(DIR))) == NULL)
		return NULL;
	dp->fd = fd;
	return dp;
}

/**
 * closedir - close a directory 
 *
 * @desc The closedir() function closes the directory stream associated with dir. 
 *       The directory stream descriptor dir is not available after this call. 
 * @return The closedir() function returns 0 on success. On error, -1 is returned, 
 *         and errno is set appropriately. 
 */
void closedir(DIR *dp){
	if (dp) {
		close(dp->fd);
		free(dp);
	}
}


/**
 * readdir - read a directory 
 *
 * @desc The readdir() function returns a pointer to a dirent structure representing 
 *       the next directory entry in the directory stream pointed to by dir. It returns 
 *       NULL on reaching the end-of-file or if an error occurred. 
 * @return The readdir() function returns a pointer to a dirent structure, or NULL 
 *         if an error occurs or end-of-file is reached. On error, errno is set appropriately. 
 */
Dirent *readdir(DIR *dp){
	struct direct dirbuf; /* local directory structure */
	static Dirent d; /* return: portable structure */
	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf)) == sizeof(dirbuf)) {
		if (dirbuf.d_ino == 0) /* slot not in use */
			continue;
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ] = '\0'; /* ensure termination */
		return &d;
	}
	return NULL;
}


/**
 * scandir  - scan a directory for matching entries 
 *
 *
 * @desc The scandir() function scans the directory dir, calling filter() on each directory entry.
 *       Entries for which filter() returns non-zero are stored in strings allocated via malloc(), 
 *       sorted using qsort() with the comparison function compar(), and collected in array namelist 
 *       which is allocated via malloc(). If filter is NULL, all entries are selected. 
 * @return The scandir() function returns the number of directory entries selected or -1 if an error occurs. 
 */
int scandir(const char *dir, struct dirent ***namelist, int(*filter)(const struct dirent *), int(*compar)(const struct dirent **, const struct dirent **)){
	DIR *dp;
    struct dirent *current, *p, **names = NULL;
	size_t arraysz, nitems = 0;
	const size_t inc = 10;

    if ( (dp = opendir(dir)) == NULL)
		return -1;

	arraysz = inc;
	names = (struct dirent **)malloc(arraysz * sizeof(struct dirent *));
	while ((current = readdir(dp)) != NULL){
		if (filter != NULL && !(*filter)(current))
			continue;
		p = (struct dirent *)malloc(sizeof(current));
		p->ino = current->ino;
		memcpy(current->name, p->name, strlen(current->name) + 1);

		if (nitems >= arraysz) {
		struct dirent **names2;
 			names2 = (struct dirent **)realloc((char *)names, (arraysz + inc) * sizeof(struct dirent *));
 			if (names2 == NULL) {
 				free(p);
				p = NULL;
 				return -1;
 			}
 			names = names2;
 			arraysz += inc;
 		}
 		names[nitems++] = p;
 	}
 	closedir(dp);
 	if (nitems && dcomp != NULL){
 		qsort(names, nitems, sizeof(struct dirent *), compar);
	}
 	*namelist = names;
 	return(nitems);
}





