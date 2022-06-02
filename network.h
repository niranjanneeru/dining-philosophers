#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#include <unistd.h>

#include "display.h"

# define IP 0

int fork_network_call(int i, int port){
    int fd = socket(AF_INET, SOCK_STREAM, IP);
    if(fd == -1){
		perror("Socket Creation Error");
        printf("\nFork %d", i);
		exit(EXIT_FAILURE);
	}
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    int addrlen = sizeof(address);
    if (bind(fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Binding Failed");
        exit(EXIT_FAILURE);
    }
    listen(fd,5);
    return fd;
}


int philosopher_network_call(int id, int fork, int port){
    int fd = socket(AF_INET, SOCK_STREAM, IP);
     if(fd == -1){
		perror("Socket Creation Error");
        printf("\nPhilosopher %d",id);
		exit(EXIT_FAILURE);
	}
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if(connect(fd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("Connection Error");
        printf("\nPhilosopher %d",id);
		exit(EXIT_FAILURE);
    }
    return fd;
}

int acquire_fork(int id, int fork, int port){
    int fd = philosopher_network_call(id,fork, port);
    int command = REQUEST;
    write(fd, &command, sizeof(command));
    write(fd, &id,sizeof(id));
    read(fd, &command, sizeof(command));
    close(fd);
    return command;
}

int release_fork(int id, int fork, int port){
    int fd = philosopher_network_call(id,fork, port);
    int command = RELEASE;
    write(fd, &command, sizeof(command));
    write(fd, &id,sizeof(id));
    read(fd, &command, sizeof(command));
    close(fd);
    return command;
}