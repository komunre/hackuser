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
#include "../../shared/defines.h"
#include "kolua.h"

int server;
int clients[maxPlayers];
int playersCounter = 0;
pthread_t accept_thread;
pthread_t clients_rw[maxPlayers];
struct sockaddr_in server_addr;

/*void* read_write_client(void* client_sock_arg){
    printf("Reading and writing new client...\n");
    int client_sock = *((int*)client_sock_arg);
    char* buf = malloc(sizeof(char)*4048);
    if (write(client_sock, "Accepted2", 4048) < 0){
        printf("no connection\n");
        return NULL;
    }
    while(1){
        int size = 0;
        while ((size = recv(client_sock, buf, 4048, 0)) > 0){
            printf("%s\n", buf);
            printf("Writing...\n");
            if (write(client_sock, buf, sizeof(buf)) < 0){
                printf("No write\n");
                return NULL;
            }
            buf = memset(buf, 0, sizeof(buf));
        }
    }
}*/

int start(int port){
    server = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
    
    
    if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("Can't bind server\n");
        return -1;
    }

    if (listen(server, 10) < 0){
        printf("Can't listen\n");
        return -1;
    }

    pid_t* forks = malloc(sizeof(pid_t)*maxPlayers);
    while (1){
        int addrlen = sizeof(server_addr);
        printf("accepting next player...\n");
        int client = accept(server, (struct sockaddr*)&server_addr, (socklen_t*)&addrlen);
        if (client < 0){
            printf("Accept error: %d\n", errno);
            continue;
        }
        /*if (pthread_create(clients_rw, NULL, read_write_client, (void*)&client) != 0){
            printf("Can't create thread\n");
        }*/
        forks[playersCounter] = fork();
        if (forks[playersCounter] < 0){
            printf("Fork failed\n");
            return -1;
        }
        else if (forks[playersCounter] == 0){
            printf("Reading and writing new client...\n");
            char* buf = malloc(sizeof(char)*MSG_SIZE);
            memset(buf, '\0', MSG_SIZE);
            while(1){
                int size = 0;
                if (read(client, buf, MSG_SIZE) > 0){
                    char* result = exec_lua_file(buf);
                    printf("%s\n", buf);
                    printf("Writing...\n");
                    if (write(client, result, MSG_SIZE) < 0){
                        printf("No write\n");
                        return -1;
                    }
                    buf = memset(buf, 0, MSG_SIZE);
                }
                if (size == -1){
                    printf("Reading failed\n");
                    return -1;
                }
            }
        }
        playersCounter++;
    }
    return 0;
}
