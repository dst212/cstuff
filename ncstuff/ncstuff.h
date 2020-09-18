/*
 * Copyright (C) 2020 Emanuele De Stefani <212dst212@gmail.com>
 * This work is licensed under the LGPLv3, see /LICENSE
 */

//header used for some ncurses function

#ifndef __NCSTUFF_H
#define __NCSTUFF_H

#include <stdarg.h>
#include <stdlib.h>
#include <ncurses.h>

#include "../strstuff/strstuff.h"
#include "../miscstuff/miscstuff.h"

//menus' switch-case macros
#define NC_EXIT 27
#define NC_ENTER (int)'\n'
#define QUIT_KEYS 'q': case NC_EXIT: case KEY_EXIT //to use in a switch-case
#define isQuitKey(ch) (tolower(ch) == 'q' || ch == NC_EXIT  || ch == KEY_EXIT)

extern void ncflags(WINDOW*);
extern int ncignoreinput(WINDOW*);

//colors functions
extern void nccolors(void);
#define setcolor(w, c)		wattron((w), COLOR_PAIR((c)))
#define unsetcolor(w, c)	wattroff((w), COLOR_PAIR((c)))
#define setbgcolor(w, c)	wbkgd(w, COLOR_PAIR((c)))
#define fgcolor(c)			((c) & 0b1111)						//get foreground color from c
#define bgcolor(c)			((c) & 0b11110000)					//get background color from c
#define revcolor(c)			((fgcolor(c) << 4) | ((c) >> 4))	//reverse background and foreground

//printing functions
extern void ncfillrow(WINDOW*, const int, const int, int, const char, const short);
extern void ncfillcol(WINDOW*, const int, const int, int, const char, const short);
extern void ncfillwin(WINDOW*, const char, const short);

extern size_t ncprint(WINDOW*, const char*, ...);
extern size_t ncprintv(WINDOW*, const char*);
#define mvncprint(w, y, x, msg, ...)	(wmove((w), (y), (x)) == ERR ? ERR : ncprint((w), msg __VA_OPT__(,) __VA_ARGS__))
#define mvncprintv(w, y, x, msg, ...) (wmove((w), (y), (x)) == ERR ? ERR : ncprintv((w), msg __VA_OPT__(,) __VA_ARGS__))
//print a colorful message and wait for a input key to be pressed
#define ncpause(w, msg, ...)			do { ncprint((w), msg __VA_OPT__(,) __VA_ARGS__); wrefresh(w); wgetch(w); waddch(w, '\n'); } while(0)
#define mvncpause(w, y, x, msg, ...)	do { wmove((w), (y), (x)); ncpause((w), msg __VA_OPT__(,) __VA_ARGS__); } while(0)

#define nctempmsg(w, y, x, msg, ...)	do { \
	if(w != NULL) delwin(w); \
	w = newwin(1, 0, y, x); \
	mvncprint(w, 0, 0, msg __VA_OPT__(,) __VA_ARGS__); \
	wrefresh(w); \
	delwin(w); \
} while(0);
//I don't like the above macro, probably will be removed

//input functions
extern size_t ncscan(const int, const int, const int, const int, const int, char*, const char*, const short);
extern char ncask(WINDOW*, const char*, const char*);

extern short ncnumber(WINDOW*, const short, const short, short*, const short min, const short);
extern int8_t ncnumberchar(WINDOW*, const short, const short, int8_t*, const short min, const short);

#define NC_POPUP_OK		"Ok"
#define NC_POPUP_YES	"Yes"
#define NC_POPUP_NO		"No"
#define NC_POPUP_CENTER(w, height, width)	(getmaxy(w) - height) / 2, (getmaxx(w) - width) / 2, height, width
extern void ncpopup_printmsg(WINDOW*, const int, const int, const bool, const size_t, const char*, int*);

extern void ncpopup_info(const int, const int, int, const int, const short, const char*, const char*);
extern void ncpopup_bool(const int, const int, int, const int, const short, const char*, const char*, const char*);

extern int ncmenu(const int, const int, const int, const int, const char**, const short, const short);

#include "ncstuff.c"

#endif
//END
