/*
 * Copyright (C) 2020 Emanuele De Stefani <212dst212@gmail.com>
 * This work is licensed under the LGPLv3, see /LICENSE
 */

//This header is part of cstuff
//header used for some ncurses function

#ifndef __NCSTUFF_H
#define __NCSTUFF_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#define msleep(ms) usleep((ms) * 1000)
#include <ncurses.h>

#include "strstuff.h"

#define ncflags(w) do { /*cbreak(); noecho();*/ keypad(w, true); nodelay(w, false); scrollok(w, false); } while(0)

#define NC_EXIT 27
#define NC_ENTER (int)'\n'
#define QUIT_KEYS 'q': case NC_EXIT: case KEY_EXIT //to use in a switch-case
#define isQuitKey(ch) (tolower(ch) == 'q' || ch == NC_EXIT  || ch == KEY_EXIT)

int ncignoreinput(WINDOW*w) {
	//catch and ignore all the pressed keys
	int r = ERR, ignored = ERR;
	bool was_nodelay = is_nodelay(w);
	if(!(was_nodelay = is_nodelay(w)))
		nodelay(w, true);
	while((ignored = wgetch(w)) != ERR)
		r = ignored;
	if(!was_nodelay)
		nodelay(w, false);
	//returns the last one caugth
	return r;
}

void nccolors(void) { //color init
	int i;
	if(has_colors()) {
		start_color();
		for(i = 0; i < 256; i++)
			init_pair(i, i % 16, i / 16);
	} else {
		wprintw(stdscr, "This terminal doesn't support colors.");
		wgetch(stdscr);
		waddch(stdscr, '\n');
	}
}
#define setcolor(w, c)		wattron(w, COLOR_PAIR((c)))
#define unsetcolor(w, c)	wattroff(w, COLOR_PAIR((c)))
#define setbgcolor(w, c)	wbkgd(w, COLOR_PAIR((c)))
#define fgcolor(c)			((c) & 0b1111)						//get foreground color from c
#define bgcolor(c)			((c) & 0b11110000)					//get background color from c
#define revcolor(c)			((fgcolor(c) << 4) | ((c) >> 4))	//reverse background and foreground

//fill a row with c at y from x for dx in w
void ncfillrow(WINDOW*w, const int y, const int x, int dx, const char c, const short color) {
	int i;
	setcolor(w, color);
	wmove(w, y, x);
	if(dx == -1) dx = getmaxx(w);
	for(i = 0; i < dx; i++)
		waddch(w, c);
	wmove(w, y, x);
}

//fill a column with c at x from y for dy in w
void ncfillcol(WINDOW*w, const int y, const int x, int dy, const char c, const short color) {
	int i;
	setcolor(w, color);
	if(dy == -1) dy = getmaxy(w);
	for(i = 0; i < dy; i++)
		mvwaddch(w, y + i, x, c);
	wmove(w, y, x);
}

//fill a whole window with c
void ncfillwin(WINDOW*w, const char c, const short color) {
	int i, j;
	setcolor(w, color);
	wmove(w, 0, 0);
	for(i = 0; i < getmaxy(w); i++)
		for(j = 0; j < getmaxx(w); j++)
			waddch(w, c);
	wmove(w, 0, 0);
}

//colorful output, still not formatted like printf() / wprintw()
size_t ncprint(WINDOW*w, const char*o /*output str*/, ...) {
	#define triggerChar '@'
	/*Considering @ as trigger char,
		ncprint(stdscr, "@FAHello @PWorld!\n", 15);
	is the same as
	 	wattron(stdscr, COLOR_PAIR(0xFA));
		addstr("Hello ");
		wattron(stdscr, COLOR_PAIR(15));
		addstr("World!\n");
	The first one is obviously faster to type and easier to remember too, though
	it's slower during the execution.
	The first letter is referred to the background color, the second one to the
	foreground, see nccolors(). If you use X instead of the bg color, the
	default color is used. Note that you can use "@P" to pass the color as an
	argument (each "@P" needs an argument).*/
	size_t l = strlen(o), ol = l;
	int i;
	char toParse[2+1] = "";
	va_list va;
	va_start(va, o);
	for(i = 0; i < l; i++) {
		switch (o[i]) {
			default:
				waddch(w, o[i]);
				break;
			case triggerChar:
				//copy content of output string to toParse
				//may be useful with bigger strings to parse, in future
				//it's here just as a note
				// strncpy(toParse, o + i, 2); i += 2;
				ol--;
				if((toParse[0] = o[++i]) == triggerChar)
					waddch(w, triggerChar);
				else if(toupper(toParse[0]) == 'P')
					setcolor(w, va_arg(va, int));
				else {
					toParse[1] = o[++i];
					if(toupper(toParse[0]) == 'X')
						setcolor(w, getbkgd(w) + str2num(toParse + 1, 0x10));
					else //parse the hex string and turn it into a color pair id
						setcolor(w, str2num(toParse, 0x10));
					ol-=2;
				}
				break;
			case '%':
				switch(o[++i]) {
					default: case '%':
						waddch(w, '%');
					case 's':
						waddstr(w, va_arg(va, char*));
				}
		}
	}
	va_end(va);
	#undef triggerChar
	return ol;
}
#define mvncprint(w, y, x, msg, ...)	(wmove((w), (y), (x)) == ERR ? ERR : ncprint((w), msg __VA_OPT__(,) __VA_ARGS__))

//print in vertical (not formatted nor colorful yet)
void ncprintv(WINDOW*w, const char*msg) {
	size_t i, l = strlen(msg);
	short x = getcurx(w), y = getcury(w);
	for(i = 0; i < l; i++)
	mvwaddch(w, y + i, x, msg[i]);
	wmove(w, y + i, x); //ready to print in vertical again
}
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
//I don't like the above macro. Actually I don't like all the macros I wrote

//number input
void ncnumber(WINDOW*w, const short y, const short x, short*toChange, const short min, const short max) {
	int ch;
	do {
		mvwprintw(w, y, x, "%3d\b", *toChange);
		wrefresh(w);
		ch = wgetch(w);
		switch(ch) {
			case KEY_UP:
				++(*toChange);
				break;
			case KEY_DOWN:
				--(*toChange);
				break;
		}
		if(*toChange < min) *toChange = max;
		else if(*toChange > max) *toChange = min;
	} while(ch != KEY_ENTER && ch != NC_ENTER);
}

void ncnumberchar(WINDOW*w, const short y, const short x, int8_t*toChange, const short min, const short max) {
	short n = (short)*toChange;
	ncnumber(w, y, x, &n, min, max);
	*toChange = (int8_t)n;
}

//ask for a question, waiting for a key press which matches with answer's range (see chrange() in strstuff.h)
char ncask(WINDOW*w, const char*question, const char*answer) {
	int ch;
	ncprint(w, question);
	while(!chrange(ch = wgetch(w), answer));
	return ch;
}

//wait for user input (still not completed, since if lenght is less than maxSize, the output will overflow)
size_t ncscan(const int starty, const int startx, const int length, const int maxSize, char*input, const char*allowed, const int color) {
	size_t l = strlen(input); //initial length if the string is not clear
	int i = l /*current position*/, j, ch;
	int rSize = maxSize; // right input's side length
	char*rinput = (char*)malloc(sizeof(char) * (rSize + 1)); //right side of the input
	WINDOW*w;
	w = newwin(1, length, starty, startx);
	strfill(input + l, 0, maxSize - l); //reset the array
	strfill(rinput, 0, rSize); //and also the input on the right of the cursor
	/*	rinput is used as a faster way instead of shifting all the string when a
	char is added in the middle, in the end all the ripunt content from the
	last '\0' to the end is copied to the input string	*/
	ncflags(w);
	curs_set(1);
	setcolor(w, color);
	mvwaddstr(w, 0, 0, input);
	setbgcolor(w, color);
	wrefresh(w);
	// ncfillrow(w, 0, 0, length, ' ', color);
	while((ch = wgetch(w)) != NC_ENTER && ch != KEY_ENTER) {
		switch(ch) {
			case ERR:
				break;
			case KEY_BACKSPACE: //remove last char from input
				if(i > 0) {
					input[--i] = 0;
					l--;
					mvwdelch(w, 0, i);
				}
				break;
			case KEY_DC: //DELETE KEY
				if(i < l) {
					rinput[rSize-((l--)-i)] = 0;
					wdelch(w);
				}
				break;
			case KEY_LEFT:
				if(i > 0) {
					i--;
					rinput[rSize-(l-i)] = input[i];
					input[i] = 0;
					waddch(w, '\b');
				}
				break;
			case KEY_RIGHT:
				if(i < l) {
					input[i] = rinput[rSize-(l-i)];
					rinput[rSize-(l-i)] = 0;
					waddch(w, input[i++]);
				}
				break;
			default:
				if(l < maxSize && l < length && chrange(ch, allowed)) { //the char is in the allowed range
					input[i++] = ch;
					l++; //length is increased
					waddch(w, ch);
					for(j = rSize - (l - i); j < rSize; j++)
						waddch(w, rinput[j]);
					wmove(w, 0, i);
				}
				break;
		}
		wrefresh(w);
	}
	if(i < l)
		strcpy(input+i, rinput+(rSize-(l-i)));
	wclear(w);
	wrefresh(w);
	wmove(w, starty, startx);
	delwin(w);
	free(rinput);
	return l;
}

void ncpopup_printmsg(WINDOW*w, const int height, const int width, const bool is_oneline, const size_t outputlenght, const char*output, int*jolly_var) {
	int i;
	if(is_oneline) {
		mvwaddnstr(w, 2, 2, output + *jolly_var, width);
		if(outputlenght - *jolly_var < width) {
			waddstr(w, "   ");
			waddnstr(w, output + *jolly_var, width - (outputlenght - *jolly_var) - 2);
		}
		*jolly_var = (*jolly_var + 1) % outputlenght;
	} else {
		*jolly_var = 0;
		for(i = 0; i < height && *jolly_var == 0; i++) {
			mvwaddnstr(w, i + 1, 1, width * i + output, width);
			if(strlen(width * i + output) <= width) *jolly_var = 1;
		}
		if(*jolly_var == 0)
			mvwaddstr(w, getcury(w), getcurx(w) - 3, "...");
	}
}

#define NC_POPUP_CENTER(w, height, width)	(getmaxy(w) - height) / 2, (getmaxx(w) - width) / 2, height, width
//print a popup with an info and an "OK" button
void ncpopup_info(const int starty, const int startx, int height, const int width, const short color, const char*output, const char*ok_msg) {
	const size_t outputlenght = strlen(output);
	if(height <= 0)
		height = outputlenght / width;
	const bool is_oneline = (height == 1 && outputlenght > width);
	int ch = ERR, jolly_var = 0 /*either a flag or a "shift-index"*/;
	WINDOW*w;
	w = newwin(height + 3, width + 2, starty - 1, startx - 1);
	curs_set(0);
	ncflags(w);
	setcolor(w, color);
	setbgcolor(w, color);
	if(is_oneline)
		nodelay(w, true);
	do {
		ncpopup_printmsg(w, height, width, is_oneline, outputlenght, output, &jolly_var);
		mvncprint(w, height + 3 - 2, width / 2 + 2/*padding*/ - (strlen(ok_msg) + 2) / 2, "@P %s @P", revcolor(color), ok_msg, color);
		wrefresh(w);
		if(is_oneline)
			msleep(200);
	} while((ch = wgetch(w)) != NC_ENTER && ch != KEY_ENTER);
	wclear(w);
	delwin(w);
}

#define NC_POPUP_YES "Yes"
#define NC_POPUP_NO "No"
//print a popup with a "binary question" (YES/NO)
bool ncpopup_bool(const int starty, const int startx, int height, const int width, const short color, const char*output, const char*yes_msg, const char*no_msg) {
	const size_t outputlenght = strlen(output);
	if(height <= 0)
		height = outputlenght / width;
	const bool is_oneline = (height == 1 && outputlenght > width);
	const int width_shift = (strlen(yes_msg) + strlen(no_msg) + 5) / 2; //yes and no's size + blank spaces
	bool r = true;
	int ch = ERR, jolly_var = 0;
	WINDOW*w;
	w = newwin(height + 3, width + 2, starty - 1, startx - 1);
	curs_set(0);
	ncflags(w);
	setcolor(w, color);
	setbgcolor(w, color);
	if(is_oneline)
		nodelay(w, true);
	do {
		switch(ch) {
			case ERR: case KEY_ENTER: case NC_ENTER:
			break;
			case KEY_LEFT:
			case KEY_RIGHT:
			r = !r;
			break;
		}
		ncpopup_printmsg(w, height, width, is_oneline, outputlenght, output, &jolly_var);
		mvncprint(w, height + 3 - 2, width / 2 + 2 - width_shift,
			"@P %s @P @P %s @P",
			r ? revcolor(color) : color,
			yes_msg,
			color,
			r ? color: revcolor(color),
			no_msg,
			color
		);
		if(is_oneline)
			msleep(200);
		wrefresh(w);
	} while((ch = wgetch(w)) != NC_ENTER && ch != KEY_ENTER);
	delwin(w);
	return r;
}

//simple menu with some options
int ncmenu(const int starty, const int startx, const int height, const int width, const char**choices, const short color, const short hlcolor) {
	int i, ch = 0;
	WINDOW*w;
	w = newwin(height, width - 1, starty, startx);
	curs_set(0);
	ncflags(w);
	wmove(w, 0 , 0);
	setcolor(w, color);
	for(i = 0; i < height; i++)
		mvncprint(w, i, 0, choices[i]);
	i = 0;
	do {
		setcolor(w, hlcolor); mvncprint(w, i, 0, choices[i]);
		wrefresh(w);
		ch = wgetch(w);
		setcolor(w, color); mvncprint(w, i, 0, choices[i]);
		switch(ch) {
			case KEY_DOWN:
				i = (i + 1) % height;
				break;
			case KEY_UP:
				i = (i <= 0 ? height : i) - 1;
				break;
			default:
				//jump to an 1-indexed option if a number is pressed
				if('1' <= ch && ch <= '9') {
					i = ch - (int)'1';
					if(i >= height)
						i = height-1;
				}
				break;
		}
	} while(ch != KEY_ENTER && ch != NC_ENTER && ch != ' ');
	wclear(w);
	wrefresh(w);
	delwin(w);
	curs_set(1);
	return i;
}

#endif
//END
