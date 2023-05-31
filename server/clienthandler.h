#pragma once

#include <arpa/inet.h>
#include <stdbool.h>

typedef struct {
    char ip_address[INET_ADDRSTRLEN];
    int port;
    bool in_use;
} client_t;

void* handle_client(void* arg);