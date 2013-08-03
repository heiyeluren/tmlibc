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
 * $Id: ctype.c 2008-11-09 01:06 heiyeluren $
 */


#include "ctype.h"


/**
 * isalnum - checks for an alphanumeric character
 * 
 * @desc it is equivalent to (isalpha(c) || isdigit(c))
 */
int isalnum(int c){
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= 0x30 && c <= 0x39));
}

/**
 * isalpha - checks  for  an  alphabetic  character
 *
 * @desc in the standard "C" locale, it is equivalent to (isupper(c) || islower(c)).  In some 
 *		 locales, there may be additional characters for which isalpha() is true--letters
 *       which are neither upper case nor lower case.
 */
int isalpha(int c){
	return ( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') );
}

/**
 * isascii - checks whether c is a 7-bit unsigned char value that fits into the ASCII character set.
 *
 * @desc ASCII 0-127
 */
int isascii(int c){
	return (c >= 0x00 && c <= 0x7f);
}

/**
 * isblank - checks for a blank character; that is, a space or a tab
 */
int isblank(int c){
	return (c == ' ' || c == '\t');
}

/**
 * iscntrl - checks for a control character
 *
 * @desc ASCII 0-30
 */
int iscntrl(int c){
	return (c >= 0x00 && c <= 0x1d);
}

/**
 * isdigit - checks for a digit (0 through 9)
 */
int isdigit(int c){
	return (c >= '0' && c <= '9');
}

/**
 * isgraph - checks for any printable character except space
 *
 * @desc ASCII 21-126
 */
int isgraph(int c){
	return (c >= 0x21 && c <= 0x7e);
}

/**
 * islower - checks for a lower-case character ('a' through 'z')
 */
int islower(int c){
	return (c >= 'a' && c <= 'z');
}

/**
 * isprint - checks for any printable character including space
 *
 * @desc ASCII 20-126
 */
int isprint(int c){
	return (c >= 0x20 && c <= 0x7e);
}

/**
 * ispunct - checks for any printable character which is not a space or an alphanumeric character
 */
int ispunct(int c){
	return ( (c >= 0x21 && c <= 0x7e) && !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= 0x30 && c <= 0x39)) );
}

/**
 * isspace - checks  for white-space characters
 *
 * @desc In the "C" and "POSIX" locales, these are: space, form-feed ('\f'), newline ('\n'), 
 *		 carriage return ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
 */
int isspace(int c){
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || c == '\f');
}

/**
 * isupper - checks for an uppercase letter
 */
int isupper(int c){
	return (c >= 'A' && c <= 'Z');
}

/**
 * isxdigit - checks for a hexadecimal digits, that is, one of "0123456789abcdefABCDEF"
 */
int isxdigit(int c){
	return ( (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f') );
}


/**
 * toascii - convert a byte to 7-bit ASCII
 */
int toascii(int c){
	return c & 0x7f;
}

/**
 * tolower -- upper case to lower case letter conversion
 */
int tolower(int c){
	return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

/**
 * toupper - lower case to upper case letter conversion
 */
int toupper(int c){
	return (c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c;
}


