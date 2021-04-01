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

int client;
char* buf;
int start_client(const char* ip, int port){
	client = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip);
	if (connect(client, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
		logko("Error connecting");
		flush();
		return -1;
	}
	return 0;
}

void send_data(char* message){
	buf = malloc(sizeof(char)*MSG_SIZE);
	char* fullmsg = malloc(MSG_SIZE + sizeof(char));
	strcpy(fullmsg, message);
	memset(fullmsg, '\0', MSG_SIZE);
	if (write(client, message, MSG_SIZE) < 0){
		logko("Error write\n");
		flush();
		return;
	}
	if (read(client, buf, MSG_SIZE) < 0){
		logko("Read error\n");
		flush();
		return;
	}
	logko(buf);
	logko("\n");
	flush();
}