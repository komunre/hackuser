#include "buffers.h"
#include <curses.h>

lineRow = 15;
void printBuffer(){
	for (int y = 0; y < lineRow; y++){
		for (int i = 0; i < cols; i++){
			mvaddch(y, i, buffer[y*cols+i]);
		}
	}
}