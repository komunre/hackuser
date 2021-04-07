#ifndef LUA_FUNCS_H
#define LUA_FUNCS_H

#include "../../shared/defines.h"
#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>
#include <stdlib.h>

void sendMessage(lua_State* L);
int transfer(lua_State* L);
int split(lua_State* L);

#endif