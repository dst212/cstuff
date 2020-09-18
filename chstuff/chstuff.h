/*
 * Copyright (C) 2020 Emanuele De Stefani <212dst212@gmail.com>
 * This work is licensed under the LGPLv3, see /LICENSE
 */

//This header is part of cstuff
//Stuff for wide characters

#ifndef __CHSTUFF_H
#define __CHSTUFF_H

#include <wchar.h>
#include <locale.h>

#define CHSTUFF_GROUP 11

#define CHSTUFF_BORDERS 124
extern wchar_t charBorders(int);

#define CHSTUFF_SYMBOLS 13
extern wchar_t charSymbol(int);

#include "chstuff.c"

#endif
//END
