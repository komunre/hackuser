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
    char* msg = lua_tostring(L, 0);
    for (int i = 0; i < maxPlayers; i++){
        printf("Sending message to %d\n", clients[i]);
        write(clients[i], msg, MSG_SIZE);
    }
}