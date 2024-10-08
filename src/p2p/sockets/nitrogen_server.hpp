#ifndef NITROGEN_SERVER_H
#define NITROGEN_SERVER_H

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

namespace network{
class NetworkServer{
    public: 
    NetworkServer(const NetworkServer& netserve);
    void Network_activate_block_server(int argc, char **argv);
};
}
#endif