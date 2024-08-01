#ifndef NITROGEN_CLIENT_H
#define NITROGEN_CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <thread>
#include <cstddef>
#include <stdlib.h>
#include <unistd.h>

class NetworkClient{
    public: 
    NetworkClient(const NetworkClient& netserve);
    void Network_activate_block_client(int argc, char **argv);
    void client_error(const char* msg){perror(msg); exit(1);}
};

int main(){}
#endif