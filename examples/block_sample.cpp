#include <iostream>
#include <string>
#include <chrono>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <unistd.h>
#include "../src/block/block.hpp"

using namespace std::chrono;

void broadcast_block_creation(int argc, char** argv)
{
    int sockfd, newsockfd, portno;
    ssize_t ios; struct sockaddr_in *server, *client;
    char buffer[256]; socklen_t clength;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) perror("sockerr");
    portno = atoi(argv[1]);
    memset((char*)&server,0, sizeof(server));
    server->sin_family = AF_INET;
    server->sin_port = htons(portno);
    server->sin_addr.s_addr = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr*)&server,sizeof(server)) < 0)
        perror("binderr"); exit(EXIT_FAILURE);
    const int max_listen_nodes = 10;
    if (listen(sockfd, max_listen_nodes) < 0)
        perror("listen err"); exit(EXIT_FAILURE);
    clength = sizeof(client);
    newsockfd = accept(sockfd, (struct sockaddr*)&server,&clength);
    if (newsockfd < 0) perror("accept err");
    const bool poll_incoming = true;
    while(poll_incoming){
        memset(buffer, 0, sizeof(buffer));
        ios = read(newsockfd, buffer, strlen(buffer));
        std::cout << buffer << std::endl;
        if (ios < 0) perror("read err"); exit(1);
        fgets(buffer, sizeof(buffer), stdin);
        ios = write(newsockfd,buffer,strlen(buffer));
        if (ios < 0) perror("write err"); exit(1);
    }
}

void block_sample(int cmd, char** cmdargs)
{
    struct Block* new_block_init = new Block();
    Blockstructure* new_block_struct = new Blockstructure();
    new_block_struct->block_id= 1;
    new_block_struct->transaction_time = high_resolution_clock::now();
    new_block_struct->tx_amount = 20;
    new_block_struct->block_header = "sample_header";

    Node* snode = new Node();
    Node* rnode = new Node();
    snode->balance = 300;
    snode->preceding_node = nullptr;
    
    rnode->balance = 400;
    rnode->preceding_node = nullptr;

    BlockTxDetails* new_blockTx_data = new BlockTxDetails();
    new_blockTx_data->sender = snode;
    new_blockTx_data->receiver = rnode;
    new_blockTx_data->tx_hash = "sample_hash";

    new_block_struct->block_tx_details.receiver = new_blockTx_data->receiver;
    new_block_struct->block_tx_details.sender = new_blockTx_data->sender;
    new_block_struct->block_tx_details.tx_hash = new_blockTx_data->tx_hash;

    BlockOps<std::string>* new_block_opx = new BlockOps<std::string>();
    BlockOps<std::string> block_opx_init = new_block_opx->create_new_blockops(*new_block_struct);
    Block* block_created = new_block_init->create_new_block(block_opx_init);
    if (block_created->block_hash > 0) broadcast_block_creation(cmd, cmdargs);
    free(new_block_struct);
    free(new_block_opx);
    free(new_block_init);
}

int main(int argc, char** argv)
{
    if(argc < 2) perror("invalid no of args");exit(1);
    block_sample(argc, argv);
    return 0;
}