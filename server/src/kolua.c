#include "kolua.h"

#include <lua.h>


#include "../../shared/defines.h"
#include "lua_funcs.h"

lua_State* L;

void init_lua(){
    printf("Initializing lua...");
    L = luaL_newstate();
    luaL_openlibs(L);

    lua_register(L, "send_msg", sendMessage);
    lua_register(L, "transfer", transfer);
    lua_register(L, "create_acc", create_account);
    lua_register(L, "db_get", access_db);
    lua_register(L, "db_set", access_db_set);
}

char* exec_lua_file(char* file, char* args){
    lua_pushstring(L, args);
    lua_setglobal(L, "args");
    luaL_dofile(L, file);
    return lua_tostring(L, -1);
}