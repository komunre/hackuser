#include "client.h"
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "logging.h"
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "../../shared/defines.h"
#include "buffers.h"
#include <curses.h>
#include <poll.h>
#include <errno.h>

int client;
char* buf;
pthread_t chat;

void* read_chat(){
	char* msg_buf = malloc(MSG_SIZE);
	while (1){
		if (read(client, msg_buf, MSG_SIZE) < 0){
			continue;
		}
		
		flush();
	}
}

void* rw_data(){
	char* rw_buf = malloc(MSG_SIZE);
	while (1){
		struct pollfd pfd[1];
		pfd[0].fd = client;
    	pfd[0].events = POLLIN;
    	int rv = poll(pfd, 1, 100);
    	if (rv == -1){
        	logko("poll error");
			flush();
       		return NULL;
    	}
    	if (pfd[0].revents & POLLIN){
			if (read(client, rw_buf, MSG_SIZE) < 0){
				logko("Error read");
				flush();
				return NULL;
			}
			logko(rw_buf);	
			for (int i = 0; i < cols; i++){
				buffer[counter*cols+i] = rw_buf[i];
				mvaddch(counter, i, rw_buf[i]);
			}
			counter++;
			printBuffer();
		}
	}
}


int start_client(const char* ip, int port){
	client = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip);

	if (connect(client, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 && errno != EINPROGRESS){
		printf("Error connecting: %d", errno);
		flush();
		return -1;
	}

	pthread_create(&chat, NULL, rw_data, NULL);
	
	return 0;
}

void send_data(char* message){
	buf = malloc(sizeof(char)*MSG_SIZE);
	char* fullmsg = malloc(MSG_SIZE + sizeof(char));
	strcpy(fullmsg, message);
	memset(fullmsg, '\0', MSG_SIZE);
	if (write(client, message, MSG_SIZE) < 0){
		logko("Write error");
		return;
	}
}

/*void send_data(char* message){
	buf = malloc(sizeof(char)*MSG_SIZE);
	char* fullmsg = malloc(MSG_SIZE + sizeof(char));
	strcpy(fullmsg, message);
	memset(fullmsg, '\0', MSG_SIZE);
	struct pollfd pfd[1];
	pfd[0].fd = client;
    pfd[0].events = POLLIN | POLLOUT;
	int rv = poll(pfd, 1, 3000);
    if (rv == -1){
        logko("poll error");
		flush();
       	return;
	}
	rv = poll(pfd, 1, 3000);
	if (pfd[0].revents & POLLOUT && write(client, message, MSG_SIZE) < 0){
		logko("Error write\n");
		flush();
		return;
	}
	if (pfd[0].revents & POLLIN && read(client, buf, MSG_SIZE) < 0){
		logko("Read error");
		flush();
		return;
	}
	for (int i = 0; i < cols; i++){
		buffer[counter*cols+i] = buf[i];
		mvaddch(counter, i, buf[i]);
	}
	counter++;
	printBuffer();
	rv = poll(pfd, 1, 1000);
	if (pfd[0].revents & POLLIN && read(client, buf, MSG_SIZE) < 0){
		return;
	}
	for (int i = 0; i < cols; i++){
		buffer[counter*cols+i] = buf[i];
		mvaddch(counter, i, buf[i]);
	}
	counter++;
	printBuffer();
}*/