#include "server.h"
#include <stdio.h>

int main(int argc, char** argv){
	printf("Launchin server...\n");
	int port = 0;
	sscanf(argv[1], "%d", &port);
	return start(port);
}
