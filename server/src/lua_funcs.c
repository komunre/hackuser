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

void sendMessage(lua_State* L){
    const char* msg = lua_tostring(L, 1);
    printf("%s\n", msg);
    for (int i = 0; i < playersCounter; i++){
        write(clients[i], msg, MSG_SIZE);
    }
}