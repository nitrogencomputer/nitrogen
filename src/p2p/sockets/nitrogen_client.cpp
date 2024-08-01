#include "nitrogen_client.hpp"

void NetworkClient::Network_activate_block_client(int argc, char **argv)
{
    if (argc < 3)
        client_error("invalid args");
    int sockfd, portno;
    ssize_t ion;
    struct sockaddr_in *client;
    char buffer[256];
    struct hostent *server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        client_error("socket error");
    portno = atoi(argv[2]);
    memset((char *)&client, 0, sizeof(client));
    client->sin_family = AF_INET;
    memcpy((char *)server->h_addr, (char *)&client->sin_addr, server->h_length);
    client->sin_addr.s_addr = INADDR_ANY;
    client->sin_port = htons(portno);
    server = gethostbyname(argv[2]);
    if (server == nullptr)
        client_error("server error");
    if (connect(sockfd, (struct sockaddr *)&client, sizeof(client)) < 0)
        client_error("connect error");
    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);
        ion = write(sockfd, buffer, sizeof(buffer));
        if (ion < 0)
            client_error("cwrite error");
        ion = read(sockfd, buffer, sizeof(buffer));
        if (ion < 0)
            client_error("cread error");
    }
    close(sockfd);
}
