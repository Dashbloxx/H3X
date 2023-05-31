#include <pthread.h>

#include "comserver.h"

int main() {
    pthread_t comserver_thread;
    pthread_create(&comserver_thread, NULL, &comserver, NULL);
    return 0;
}