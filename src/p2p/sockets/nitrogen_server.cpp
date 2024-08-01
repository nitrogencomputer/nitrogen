#include "nitrogen_server.hpp"
using namespace network;

static int max_conn = 5;
void network_error(const char *msg);
void NetworkServer::Network_activate_block_server(int argc, char **argv)
{
    if (argc < 2)
        network_error("invalid args");
    int sockfd, newsockfd, portno;
    ssize_t ion;
    struct sockaddr_in server, client;
    char buffer[256];
    socklen_t client_len;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <= 0)
        network_error("conn error");
    portno = atoi(argv[1]);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(&server)) <= 0)
        network_error("bind error");
    if (listen(sockfd, max_conn) <= 0)
        network_error("listening error");
    client_len = sizeof(client);
    newsockfd = accept(sockfd, (struct sockaddr *)&client, &client_len);
    if (newsockfd < 0)
        network_error("incoming error");
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        ion = read(newsockfd, buffer, sizeof(buffer));
        if (ion < 0)
            network_error("read error");
        fgets(buffer, sizeof(buffer), stdin);
        memset(buffer, 0, sizeof(buffer));
        ion = write(newsockfd, buffer, sizeof(buffer));
        if (ion < 0)
            network_error("write error");
    }
}

void network_error(const char *msg)
{
    perror(msg);
    exit(1);
}