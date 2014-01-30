/* 
 * File:   utils.h
 * Author: jorge
 *
 * Created on November 29, 2013, 10:12 AM
 */

#ifndef UTILS_H
#define	UTILS_H

#include <string>
#include <cstdarg>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct iostring
{
    char *ptr;
    size_t len;
};

void init_string(struct iostring *s);

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct iostring *s);

std::string formatString(const std::string fmt, ...);

#endif	/* UTILS_H */

