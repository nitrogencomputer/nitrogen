#ifndef NITROGEN_CLIENT_H
#define NITROGEN_CLIENT_H

#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <thread>

class NetworkClient{
    public: 
    NetworkClient(const NetworkClient& netserve);
    void Network_activate_block_client(int argc, char **argv);
};

int main(){}
#endif