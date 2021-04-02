#include "buffers.h"
#include <curses.h>

void printBuffer(){
	for (int y = 0; y < 9; y++){
		for (int i = 0; i < cols; i++){
			mvaddch(y, i, buffer[y*cols+i]);
		}
	}
}