/*
 * Copyright (C) 2020 Emanuele De Stefani <212dst212@gmail.com>
 * This work is licensed under the LGPLv3, see /LICENSE
 */

void msleep(int ms) {
	struct timeval tv;
	tv.tv_sec  = ms / 1000;
	tv.tv_usec = (ms % 1000) * 1000;
	select (0, NULL, NULL, NULL, &tv);
}

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

//END
