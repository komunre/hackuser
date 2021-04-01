#ifndef KOLUA_H
#define KOLUA_H

#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>

void init_lua();
char* exec_lua_file(char* file, char* args);

#endif