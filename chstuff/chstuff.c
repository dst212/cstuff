/*
 * Copyright (C) 2020 Emanuele De Stefani <212dst212@gmail.com>
 * This work is licensed under the LGPLv3, see /LICENSE
 */

wchar_t charBorders(int id) {
	switch(id % CHSTUFF_BORDERS) {
		default:
		case 0: return L' ';
		case 1: return L'█';
		case 2: return L'▀';
		case 3: return L'▄';
		case 4: return L'▌';
		case 5: return L'▐';
		case 6: return L'▛';
		case 7: return L'▜';
		case 8: return L'▙';
		case 9: return L'▟';
		case 10: return L'◎';
		case 11: return L'─';
		case 12: return L'│';
		case 13: return L'┌';
		case 14: return L'┐';
		case 15: return L'└';
		case 16: return L'┘';
		case 17: return L'├';
		case 18: return L'┤';
		case 19: return L'┬';
		case 20: return L'┴';
		case 21: return L'┼';
		case 22: return L'━';
		case 23: return L'┃';
		case 24: return L'┏';
		case 25: return L'┓';
		case 26: return L'┗';
		case 27: return L'┛';
		case 28: return L'┣';
		case 29: return L'┫';
		case 30: return L'┳';
		case 31: return L'┻';
		case 32: return L'╋';
		case 33: return L'═';
		case 34: return L'║';
		case 35: return L'╔';
		case 36: return L'╗';
		case 37: return L'╚';
		case 38: return L'╝';
		case 39: return L'╠';
		case 40: return L'╣';
		case 41: return L'╦';
		case 42: return L'╩';
		case 43: return L'╬';
		case 44: return L'╼';
		case 45: return L'╽';
		case 46: return L'┍';
		case 47: return L'┑';
		case 48: return L'┕';
		case 49: return L'┙';
		case 50: return L'┝';
		case 51: return L'┥';
		case 52: return L'┯';
		case 53: return L'┷';
		case 54: return L'┿';
		case 55: return L'╾';
		case 56: return L'╿';
		case 57: return L'┎';
		case 58: return L'┒';
		case 59: return L'┖';
		case 60: return L'┚';
		case 61: return L'┠';
		case 62: return L'┨';
		case 63: return L'┸';
		case 64: return L'┰';
		case 65: return L'╂';
		case 66: return L'╌';
		case 67: return L'╎';
		case 68: return L'┄';
		case 69: return L'┆';
		case 70: return L'┈';
		case 71: return L'┊';
		case 72: return L'╍';
		case 73: return L'╏';
		case 74: return L'┅';
		case 75: return L'┇';
		case 76: return L'┉';
		case 77: return L'┋';
		case 78: return L'┞';
		case 79: return L'┟';
		case 80: return L'┡';
		case 81: return L'┢';
		case 82: return L'┦';
		case 83: return L'┧';
		case 84: return L'┩';
		case 85: return L'┪';
		case 86: return L'┭';
		case 87: return L'┮';
		case 88: return L'┱';
		case 89: return L'┲';
		case 90: return L'┵';
		case 91: return L'┶';
		case 92: return L'┹';
		case 93: return L'┺';
		case 94: return L'┽';
		case 95: return L'┾';
		case 96: return L'╀';
		case 97: return L'╁';
		case 98: return L'╃';
		case 99: return L'╄';
		case 100: return L'╅';
		case 101: return L'╆';
		case 102: return L'╇';
		case 103: return L'╈';
		case 104: return L'╉';
		case 105: return L'╊';
		case 106: return L'╒';
		case 107: return L'╕';
		case 108: return L'╘';
		case 109: return L'╛';
		case 110: return L'╞';
		case 111: return L'╡';
		case 112: return L'╤';
		case 113: return L'╧';
		case 114: return L'╪';
		case 115: return L'╓';
		case 116: return L'╖';
		case 117: return L'╙';
		case 118: return L'╜';
		case 119: return L'╟';
		case 120: return L'╢';
		case 121: return L'╥';
		case 122: return L'╨';
		case 123: return L'╫';
	}
}

wchar_t charSymbol(int id) {
	switch(id % CHSTUFF_SYMBOLS) {
		default:
		case 0: return L' ';
		case 1: return L'·';
		case 2: return L'∗';
		case 3: return L'<';
		case 4: return L'ʌ';
		case 5: return L'>';
		case 6: return L'v';
		case 7: return L'ᗣ';
		case 8: return L'ᗤ';
		case 9: return L'ᗧ';
		case 10: return L'×';
		case 11: return L'¤';
		case 12: return L'¨';
	}
}

//END
