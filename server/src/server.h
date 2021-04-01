#ifndef SERVER_H
#define SERVER_H

#define maxPlayers 120

void fatal(const char* func);
char* date();
int start(int port);

int* clients;

#endif
