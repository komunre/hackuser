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
#include <poll.h>
#include <signal.h>

int server;
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
    playersCounter = 0;
    init_lua();
    server = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
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

    printf("Allocating memory...\n");
    //pid_t* forks = malloc(sizeof(pid_t)*maxPlayers);
    clients = malloc(sizeof(int)*maxPlayers);
    fd_set readset;
    while (1){
        int addrlen = sizeof(server_addr);
        clients[playersCounter] = accept(server, (struct sockaddr*)&server_addr, (socklen_t*)&addrlen);
        if (clients[playersCounter] != -1){
            playersCounter++;
            printf("Here is %d players now\n", playersCounter);
        }
        /*if (pthread_create(clients_rw, NULL, read_write_client, (void*)&client) != 0){
            printf("Can't create thread\n");
        }*/

        for (int i = 0; i < playersCounter; i++){
            int client = clients[i];
            struct pollfd pfd[1];
            pfd[0].fd = client;
            pfd[0].events = POLLIN;
            char* buf = malloc(MSG_SIZE);
            memset(buf, '\0', MSG_SIZE);
            //if (read(client, buf, MSG_SIZE) > 0){
            int rv = poll(pfd, 1, 100);
            if (rv == -1){
                printf("poll error");
                continue;
            }
            if (pfd[0].revents & POLLIN){
                if (read(client, buf, MSG_SIZE) < 0){
                    printf("Read error");
                    continue;
                }
                printf("Message accepted\n");
                char* dir = malloc(MSG_SIZE + sizeof("scripts/"));
                strcpy(dir, "scripts/");
                int args_start = 0;
                char* args = malloc(MSG_SIZE);
                printf("Getting args\n");
                int args_start_pos = 0;
                char* file_name = malloc(MSG_SIZE);
                for (int i = 0; i < MSG_SIZE; i++){
                    if (buf[i] == ' '){
                        args_start = 1;
                        args_start_pos = i;
                    }
                    if (args_start == 0){
                        file_name[i] = buf[i];
                    }
                    if (args_start == 1){
                        args[i - args_start_pos] = buf[i];
                    }
                }
                strcat(dir, file_name);
                printf("Loading lua: %s\n", dir);
                char* result = exec_lua_file(dir, args);
                printf("%s\n", buf);
                printf("Writing...\n");
                signal (SIGPIPE, SIG_IGN);
                if (write(client, result, MSG_SIZE) < 0){
                    printf("No write\n");
                    close(client);
                    continue;
                }
                buf = memset(buf, 0, MSG_SIZE);
            }
            /*if (size == -1){
                printf("Reading failed\n");
                close(client);
            }*/
            sleep(0.10);
        }
    }
    return 0;
}
