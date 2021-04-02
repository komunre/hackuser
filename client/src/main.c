#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "logging.h"
#include "client.h"
#include "buffers.h"

cols = 50;
int lineRow = 10;


void printDesign(char* str){
	mvaddstr(lineRow, 0, "============");
	for (int i = 0; i < cols; i++){
		mvaddch(lineRow + 1, i, str[i]);
	}
}
int main(const int argc, const char **argv){
	openLog("log.txt");
	int port;
	sscanf(argv[2], "%d", &port);
	if (start_client(argv[1], port) < 0){
		return -1;
	}
	initscr();
	raw();
	cbreak();
	noecho();

	buffer = malloc(9 * cols * sizeof(char));
	
	clear();
	
	mvaddstr(2, 4, "Hello, ncurses!");
	
	
	char* str = malloc(cols * sizeof(char));
	counter = 0;
	int strCounter = 0;
	
	logko("Entering loop...\n");
	while (1){
		raw();
		clear();
		printBuffer();
		printDesign(str);
		char ch = getch();
		if (ch == '~'){
			break;
		}
		if (ch == '\n'){
			clear();
			for (int i = 0; i < cols; i++){
				buffer[counter*cols+i] = str[i];
				mvaddch(counter, i, str[i]);
			}
			counter++;
			send_data(str);
			str = malloc(cols*sizeof(char));
			strCounter = 0;
		}
		else if (ch == '\\'){
			strCounter--;
			str[strCounter] = '^';
		}
		else{
			str[strCounter] = ch;
			mvprintw(11, strCounter, "%c", ch);
			strCounter++;
		}
	}
	endwin();
	closeLog();
	return 0;
}
