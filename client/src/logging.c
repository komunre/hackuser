#include "logging.h"

void openLog(char* path){
	logFile = fopen(path, "w");
}

void logko(char* str){
	fputs(str, logFile);
}

void closeLog(){
	fclose(logFile);
}

void flush(){
	fflush(logFile);
}
