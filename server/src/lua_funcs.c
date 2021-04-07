#include "lua_funcs.h"
#include "server.h"
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "server.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include "db.h"

void sendMessage(lua_State* L){
    const char* msg = lua_tostring(L, 1);
    printf("%s\n", msg);
    for (int i = 0; i < playersCounter; i++){
        write(clients[i], msg, MSG_SIZE);
    }
}

void sql_money(int key){
    
}

int transfer(lua_State* L){
    int money = 0;
    char* sender = lua_tostring(L, 1);
    char* receiver = lua_tostring(L, 2);
    int amount = lua_tointeger(L, 3);
    char* pass = lua_tostring(L, 4);
    printf("%s:%s:%d:%s\n", sender, receiver, amount, pass);
    reply = redisCommand(rcontext, "GET %s.%s", sender, "password");
    if (strcmp(pass, reply->str) != 0){
        lua_pushstring(L, "Passwords don't match");
        return 1;
    }
    freeReplyObject(reply);
    reply = redisCommand(rcontext, "GET %s.%s", sender, "money");
    sscanf(reply->str, "%d", &money);
    freeReplyObject(reply);
    redisCommand(rcontext, "SET %s.%s %d", sender, "money", money-amount);
    reply = redisCommand(rcontext, "GET %s.%s", receiver, "money");
    sscanf(reply->str, "%d", &money);
    freeReplyObject(reply);
    redisCommand(rcontext, "SET %s.%s %d", receiver, "money", money+amount);
    lua_pushstring(L, "Success");
    return 1;
}

int access_db(lua_State* L){
    char* level1 = lua_tostring(L, 1);
    char* db = lua_tostring(L, 2);
    char* key = lua_tostring(L, 3);
    if (level1 == NULL || db == NULL || key == NULL){
        return "NULL";
    }
    reply = redisCommand(rcontext, "GET %s.%s.%s", level1, db, key);
    lua_pushstring(L, reply->str);
    freeReplyObject(reply);
    return 1;
}