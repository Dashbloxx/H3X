#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdbool.h>

#include "clienthandler.h"

/* Store client(s) data here... */
client_t clients[1024];
int client_incrementer = 0;

void* handle_client(void* arg) {
    client_incrementer++;
    int client_socket = *((int*)arg);
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    if (getpeername(client_socket, (struct sockaddr*)&client_addr, &client_addr_len) == -1) {
        perror("getpeername() failed");
        close(client_socket);
        pthread_exit(NULL);
    }

    /* Set the IP and the port on the clients... */
    inet_ntop(AF_INET, &(client_addr.sin_addr), clients[client_incrementer].ip_address, INET_ADDRSTRLEN);
    clients[client_incrementer].port = ntohs(client_addr.sin_port);
    clients[client_incrementer].in_use = true;

    printf("New client connected: %s:%d\n", client_ip, client_port);

    

    close(client_socket);
    printf("Client disconnected: %s:%d\n", client_ip, client_port);
    clients[client_incrementer].in_use = false;
    pthread_exit(NULL);
}