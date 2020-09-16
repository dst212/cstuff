/*
 * Copyright (C) 2020 Emanuele De Stefani <212dst212@gmail.com>
 * This work is licensed under the LGPLv3, see /LICENSE
 */

//This header is part of cstuff
//some string-related functions

#ifndef __STRSTUFF_H
#define __STRSTUFF_H

#include <string.h>
#include <ctype.h>

#define swap(a, b) do { (a) += (b); (b) = (a) - (b); (a) -= (b); } while(0)

void strreverse(char*input) {
	size_t i, l = strlen(input);
	for(i = 0; i < l / 2; i++)
	swap(input[i], input[l-1-i]);
}

void strfill(char*arr, const char whit, const int l) {
	int i;
	for(i = 0; i < l; i++)
		arr[i] = whit;
}

size_t findinstr(const char what, const char*where, const size_t length) {
	size_t i = 0;
	while(i < length) {
		if(where[i] == what)
			return i;
		else
			i++;
	}
	return -1;
}

int str2num(const char*input, const short base) {
	int output = 0, i;
	size_t l = strlen(input);
	for(i = (input[0] == '-' ? 1 : 0); i < l; i++)
		output = (output * base) + (input[i] > '9' ? toupper(input[i]) - 'A' + 10 : input[i] - '0');
	//if you put symbols it works anyway, but I don't care, for now
	return (input[0] == '-') ? -output : output;
}

char*num2str(int input, char*output, const short base) {
	int i;
	char c;
	if(input < 0)
		output[0] = '-';
	for(i = (input < 0 ? 1 : 0); input > 0; i++) {
		output[i] = ((c = input % base) > 9) ? c + 'A' - 10 : c + '0';
		input /= base;
	}
	output[i] = 0;
	strreverse(output);
	return output;
}

bool chrange(const char ch, const char*allowed) {
	/*Ranges like AZaz09 (which in RegEx is [A-Za-z0-9])
	If you want to allow specific chars, put a \r before them, like this:
		chrange(ch, "AZ\rdst "); //note the space after 't'
	Only uppercase letters or lowercase d, s and t and spaces will be passed.*/
	size_t i, l;
	if(allowed[0] == 0) {
		return ch >= 32 && ch < 256 && ch != 127;
	} else {
		i = 1;
		l = strlen(allowed);
		while(i < l) {
			if(allowed[i-1] == '\r')
				return (findinstr(ch, allowed + i, l - i) == -1) ? false : true;
			else if(allowed[i-1] <= ch && ch <= allowed[i])
				return true;
			else
				i += 2;
		}
	}
	return false;
}

#endif
//END
