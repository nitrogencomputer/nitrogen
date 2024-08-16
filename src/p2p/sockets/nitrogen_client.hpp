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
#include <cstdint>
#include <vector>

class NetworkClient{
    public: 
    NetworkClient(const NetworkClient& netserve);
    void Network_activate_block_client(uint16_t argc, std::vector<int> arg2);
    void client_error(const char* msg){perror(msg); exit(1);}
};
#endif