#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include "logging.h"
#include "client.h"

int cols = 50;
int lineRow = 10;

void printBuffer(char* buffer){
	for (int y = 0; y < 9; y++){
		for (int i = 0; i < cols; i++){
			mvaddch(y, i, buffer[y*cols+i]);
		}
	}
}

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
	send_data("Hello!");
	initscr();
	raw();
	cbreak();
	noecho();
	
	clear();
	
	mvaddstr(2, 4, "Hello, ncurses!");
	
	
	char* buffer = malloc(9 * cols * sizeof(char));
	char* str = malloc(cols * sizeof(char));
	int counter = 0;
	int strCounter = 0;
	
	logko("Entering loop...\n");
	while (1){
		raw();
		clear();
		printBuffer(buffer);
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
