#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>

FILE* logFile;
void openLog(char* path);
void logko(char* str);
void closeLog();
void flush();

#endif
