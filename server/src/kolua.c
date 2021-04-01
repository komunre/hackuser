#include "kolua.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "../../shared/defines.h"

lua_State* L;

void init_lua(){
    L = luaL_newstate();
    luaL_openlibs(L);
}

char* exec_lua_file(char* file){
    luaL_dofile(L, file);
    return lua_tostring(L, -1);
}