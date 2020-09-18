/*
 * Copyright (C) 2020 Emanuele De Stefani <212dst212@gmail.com>
 * This work is licensed under the LGPLv3, see /LICENSE
 */

//Misc stuff

#ifndef __MISCSTUFF_H
#define __MISCSTUFF_H

#include <stdarg.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define swap(a, b) do { (a) += (b); (b) = (a) - (b); (a) -= (b); } while(0)
extern void msleep(int);
extern int randomChoice(const unsigned short, ...);
extern int randomRange(const int, const int);

#include "miscstuff.c"

#endif
//END
