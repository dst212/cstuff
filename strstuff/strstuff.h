/*
 * Copyright (C) 2020 Emanuele De Stefani <212dst212@gmail.com>
 * This work is licensed under the LGPLv3, see /LICENSE
 */

//some string-related functions

#ifndef __STRSTUFF_H
#define __STRSTUFF_H

#include <string.h>
#include <ctype.h>

#include "../miscstuff/miscstuff.h"

extern char*strreverse(char*);

extern size_t findinstr(const char, const char*,const size_t);
extern size_t strfind(const char*, const char*);

extern int str2num(const char*, const short, const size_t);
extern char*num2str(int, char*, const short);

extern bool chrange(const char ch, const char*);

#include "strstuff.c"

#endif
//END
