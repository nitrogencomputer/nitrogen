#include "nitrogen_server.hpp"
using namespace network;

void network_error(const char*msg);
void NetworkServer::Network_activate_block_server(int argc, char **argv){
    if(argc < 2)
        network_error("invalid args passed");
    int sockfd, newsockfd, portno, std::size_t io;
    struct sockaddr_in server_address, client_address; char buffer[256];
}

void network_error(const char* msg)
{
    perror(msg);
    exit(1);
}