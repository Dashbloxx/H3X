/*
 *  commserver.c
 *  This file handles the TCP server for communicating
 *  with infected clients.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#include "comserver.h"
#include "environment.h"

void* handle_client(void* arg) {
    int client_socket = *((int*)arg);
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    if (getpeername(client_socket, (struct sockaddr*)&client_addr, &client_addr_len) == -1) {
        perror("getpeername() failed");
        close(client_socket);
        pthread_exit(NULL);
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    int client_port = ntohs(client_addr.sin_port);

    printf("New client connected: %s:%d\n", client_ip, client_port);

    // Handle client request here...

    close(client_socket);
    printf("Client disconnected: %s:%d\n", client_ip, client_port);
    pthread_exit(NULL);
}

/* Communication server thread */
void* comserver() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t thread_id;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket() failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket to a specific IP and port
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Bind to all available interfaces
    server_addr.sin_port = htons(PORT);       // Use port 12345
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind() failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("listen() failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started. Listening on port 12345...\n");

    // Accept incoming connections and handle them in separate threads
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("accept() failed");
            continue;
        }

        // Create a new thread to handle the client
        if (pthread_create(&thread_id, NULL, handle_client, &client_socket) != 0) {
            perror("pthread_create() failed");
            close(client_socket);
        }
    }

    // Close the server socket
    close(server_socket);
    pthread_exit(NULL);
}