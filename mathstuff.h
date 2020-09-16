/*
 * Copyright (C) 2020 Emanuele De Stefani <212dst212@gmail.com>
 * This work is licensed under the LGPLv3, see /LICENSE
 */

//This header is part of cstuff
//Stuff about Maths

#ifndef __MATHSTUFF_H
#define __MATHSTUFF_H

#include <stdarg.h>
#include <stdlib.h>
#include <math.h>

int randomChoice(const unsigned short choices, ...) {
	int r = 0;
	short i, c = rand() % choices + 1;
	va_list va;
	va_start(va, choices);
	for(i = 0 ; i < c; i++)
		r = va_arg(va, int);
	va_end(va);
	return r;
}

int randomRange(const int min, const int max) {
	return rand() % (min + max) + min;
}

#endif
//END
